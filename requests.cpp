#include"requests.hpp"

using namespace std;
using namespace rapidjson;

const unsigned int arbLimit = 10;
const unsigned int maxResults = 1;
const unsigned int startAt = 0;
const string arbExpand_param = "changelog";



int main(int argc, char** argv) {

    Document d;
    int multi_active;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");


    string URL, URLParams, hString, URLBase = "https://allmantesting.atlassian.net/rest/api/3/search/?", authBase = getAuth(), API_KEY = getAPI();

    CURLMcode mCode;
    auto mCurl = curl_multi_init();


    map<string, reference_wrapper<issue>> issueMap;

    vector<string> headVector(arbLimit);
    vector<CURL*>* pcVector = init_multi_vector_std(arbLimit);
    vector<string> respVector(arbLimit);


    list<string> URLParamList = { "expand=" + arbExpand_param, "maxResults=" + to_string(maxResults), "startAt=" + to_string(startAt) };

    for (auto& x : URLParamList)
    {
        URLParams += x + '&';
    }

    URLParams.pop_back();

    for (int startAt = 0; startAt < arbLimit; startAt += 1) {

        URL = URLBase + URLParams;
        curl_config_std((*pcVector)[startAt], headers, headVector[startAt], respVector[startAt], URL, authBase + API_KEY);
        curl_multi_add_handle(mCurl, (*pcVector)[startAt]);
    }

    do {

        mCode = curl_multi_perform(mCurl, &multi_active);
        if (!mCode && multi_active)
        {
            mCode = curl_multi_poll(mCurl, NULL, 0, 1000, NULL);
        }
        if (mCode) { curl_multi_cleanup(mCurl); exit(1); }

    } while (multi_active);
    

    for (auto& x : respVector)
    {
        
            d.Parse(x.c_str());
            splitResp(d, issueMap);
        
    } 

    curl_multi_cleanup(mCurl);
    curl_global_cleanup();

}

vector<CURL*>* init_multi_vector_std(const unsigned int s)
{
    vector<CURL*>* phcVector = new vector<CURL*>(s);
    for (auto& x : *phcVector) { x = curl_easy_init(); }
 
    return phcVector;
}

void curl_config_std(CURL* curl, curl_slist* pHeaders, string& hString, string& rString, const string& urlString, const string& auth)
{
    curl_easy_setopt(curl, CURLOPT_URL, urlString.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());//
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, pHeaders);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rString);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &hString);
}

void curl_config_std(CURL* curl, curl_slist* pHeaders, string& hString, string& rString, const string& urlString, const string& auth, const string& post_data)
{
    curl_easy_setopt(curl, CURLOPT_URL, urlString.c_str());
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());//
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, pHeaders);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rString);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &hString);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

}



void splitResp(Document& bulkRespParsed, map<string, reference_wrapper<issue>>& issueMap)
{
    const Value& a = bulkRespParsed["issues"];

    for (SizeType issue_ind = 0; issue_ind < a.Size(); issue_ind++) 
    {
        createIssue(a[issue_ind], issueMap);
    }
   
}

