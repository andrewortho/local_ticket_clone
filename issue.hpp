#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<list>
#include "status.h"
#pragma once

using namespace std;

class user;
class issue;
class item;
class history;
class changelog;
class progress;
class priority;
class status;


class user
{
public:
	const string& getEmailAddress(void) const { return EmailAddress; }
	const string& getDisplayName(void)const { return DisplayName; }
	const string& getTimeZone(void)const { return TimeZone; }
	const string& getAccountType(void)const { return AccountType; }
	const string& getAccountId(void) const { return AccountId; }

	void setAccountId(const string& _AccountId) { AccountId = _AccountId; }
	void setEmailAddress(const string& _emailAddress) { EmailAddress = _emailAddress; }
	void setDisplayName(const string& _DisplayName) { DisplayName = _DisplayName; }
	void setTimeZone(const string& _TimeZone) { TimeZone = _TimeZone; }
	void setAccountType(const string& _AccountType) { AccountType = _AccountType; }
	void setSelf(const string& _self) { self = _self; }
	
private:
	string AccountId;
	string EmailAddress;
	string DisplayName;
	string TimeZone;
	string AccountType;
	string self;
};

class history
{
public:
	const string& getId(void) const{ return Id; }
	const user* getAuthor(void) const { return Author; }
	const string& getDateCreated(void)const{ return dateCreated; }
	const vector<const item*>* getItems(void)const { return items; };

	void setId(const string& _id) { Id = _id; }
	void setAuthor(user* _Author) { Author = _Author; }
	void setDateCreated(const string& _dateCreated) { dateCreated = _dateCreated; }
	void setItems(vector<const item*>* _items) { items = _items; }
	~history() {
		delete Author;
		for (int i = 0; i < items->size(); i++) { delete (*items)[i];}
		items->clear();
		delete items;
	}
private:
	string Id;
	user* Author;
	string dateCreated;
	vector<const item*>* items;
};

class changelog
{
public:
	int getStartAt(void) const { return startAt; }
	int getMaxResults(void)const { return maxResults; }
	int getTotal(void)const { return total; }
	const vector<history*>* getHistory(void) { return histories; };

	void setStartAt(const int _startAt) { startAt = _startAt; }
	void setMaxResults(const int _maxResults) { maxResults = _maxResults; }
	void setTotal(const int _total) { total = _total; }
	void setHistory(vector<history*>* _histories) 
	{ histories = _histories; }

	~changelog() {
		for (int i = 0; i < histories->size(); i++) { delete (*histories)[i]; }
		histories->clear();
		delete histories;
	}


private:
	int startAt;
	int maxResults;
	int total;
	vector<history*>* histories;
};
class progress
{
private:
	int nProgress;
	int total;
};

class statusCategory
{
public:
	void setSelf(const string& _self) { self = _self; }
	void setColorName(const string& _colorName) { colorName = _colorName; }
	void setName(const string& _name) { name = _name; }
	void setId(const int _id) { id = _id; }
	void setKey(const string& _key) { key = _key; }


	const string& getSelf(void) { return self; }
	const string& getColorName(void) { return colorName; }
	const string& getName(void) { return name; }
	const int getId(void) { return id; }
	const string& getKey(void) { return key; }
private:
	string self;
	int id;
	string key;
	string colorName;
	string name;
};

class status
{
public:
	void setSelf(const string& _self) { self = _self; }
	void setDescription(const string& _description) { description = _description; }
	void setName(const string& _name) { name = _name; }
	void setId(const string& _id) { id = _id; }
	void setStatusCategory(statusCategory* _statusCategory) { StatusCategory = _statusCategory; }

	const string& getSelf(void) { return self; }
	const string& getDescription(void) { return description; }
	const string& getName(void) { return name; }
	const string& getId(void) { return id; }

	~status() { delete StatusCategory; }
private:
	string self;
	string description;
	//string iconURL;
	string name;
	string id;
	statusCategory* StatusCategory;
};

class priority
{
public:
	void setSelf(const string& _self) { self = _self; }
	void setName(const string& _name) { name = _name; }
	void setId(const string& _id) { id = _id; }

	const string& getSelf(void) { return self; }
	const string& getName(void) { return name; }
	const string& getId(void) { return id; }

private:
	string self;
	string name;
	string id;
};

class issuetype
{
public:
	const string& getSelf(void) { return self; };
	const string& getId(void)const { return id; };
	const string& getDescription(void) { return description; };
	const string& getName(void)const { return name; };
	const string& getEntityId(void)const { return entityId; };
	int getHierarchyLevel(void)const { return hierarchyLevel; };

	void setSelf(const string& _self) { self = _self; };
	void setId(const string& _id) { id = _id; };
	void setDescription(const string& _description) { description = _description; };
	void setName(const string& _name) { name = _name; };
	void setSubtasks_i(const list<const issue*>&);
	void setEntityId(const string& _entityId) { entityId = _entityId; };
	void setHierarchyLevel(const int _hierarchyLevel) { hierarchyLevel = _hierarchyLevel; };
private:
	string self;
	string id;
	string description;
	string name;
	map<string, const issue*> subtasks_i;
	list<const string*> subtasks_s;
	string avatarId;
	string entityId;
	int hierarchyLevel;
};


class type
{
public:
	void setId(const string& _id) { id = _id; }
	void setName(const string& _name) { name = _name; }
	void setInward(const string& _inward) { inward = _inward; }
	void setOutward(const string& _outward) { outward = _outward; }
	void setSelf(const string& _self) { self = _self; }

	const string& getId(void) { return id; }
	const string& getName(void) { return name; }
	const string& getInward(void) { return inward; }
	const string& getOutward(void) { return outward; }
	const string& getSelf(void) { return self; }


private:
	string id;
	string name;
	string inward;
	string outward;
	string self;
};


class linkFields
{
public:
	void setSummary(const string& _Summary) { Summary = _Summary; }
	void setStatus(status* _status) { Status = _status; }
	void setPriority(priority* _priority) { Priority = _priority; }
	void setIssueType(issuetype* _issuetype) { IssueType = _issuetype; }
	const string& getSummary(void) { return Summary; }
	const status* getStatus(void) { return Status; }
	priority* getPriority(void) { return Priority; }
	issuetype* getIssueType(void) { return IssueType; }
	~linkFields() { delete Status; delete Priority; delete IssueType; }
private:
	string Summary;
	status* Status;
	priority* Priority;
	issuetype* IssueType;
};


class linkedIssue
{
public:
	void setId(const string& _id) { id = _id; }
	void setSelf(const string& _self) { self = _self; }
	void setKey(const string& _key) { key = _key; }
	void setFields(linkFields* _Fields) { Fields = _Fields; }
	//void updateLinkedIssue(Value& postData) {//api call};
	const string& getId(void) { return id; }
	const string& getSelf(void) { return self; }
	const string& getKey(void) { return key; }
	linkFields* getFields(void) { return Fields; }

	~linkedIssue() { delete Fields; }
private:
	string id;
	string key;
	string self;
	linkFields* Fields;
};

class link
{
public:
	void setId(const string& _id) { id = _id; }
	void setSelf(const string& _self) { self = _self; }
	void setType(type* _Type) { Type = _Type; }
	void setOutwardIssue(linkedIssue* _outwardIssue) { outwardIssue = _outwardIssue; }
	void setInwardIssue(linkedIssue* _inwardIssue) { inwardIssue = _inwardIssue; }

	const string& getId(void) { return id; }
	const string& getSelf(void) { return self; }
	type* getType(void) { return Type; }
	linkedIssue* getOutwardIssue(void) { return outwardIssue; }
	linkedIssue* getInwardIssue(void) { return inwardIssue; }
	
	~link() { delete Type; delete outwardIssue; delete inwardIssue; }

private:
	string id;
	string self;
	type* Type;
	linkedIssue* outwardIssue;
	linkedIssue* inwardIssue;

};


class project
{
public:
	const string& getSelf(void) { return self; };
	const string& getId(void) { return Id; };
	const string& getKey(void) { return key; };
	const string& getName(void) { return name; };
	void setSelf(const string& _self) { self = _self; };
	void setId(const string& _id) { Id = _id; };
	void setKey(const string& _key) { key = _key; };
	void setName(const string& _name) { name = _name; };
private:
	string self;
	string Id;
	string key;
	string name;
};

class watches
{
private:
	string self;
	int watchCount;
	bool isWatching;
};


class fields
{
public:
	
	const string& getStatusCategoryChangeDate(void) { return statuscategorychangedate; };
	const issuetype& getIssueType(void) { return Issuetype; };
	const string& getTimeSpent(void) { return timeSpent; };
	const project& getProject(void) { return Project; };
	const list<const string*>& getFixVersions(void) { return fixVersions; };
	int getAggregateTimeSpent(void) { return AggregateTimeSpent; };
	const string& getResolution(void) { return resolution; };
	const string& getResolutionDate(void) { return resolutionDate; };
	int getWorkRatio(void) { return workRatio; };
	const watches& getWatches(void) { return Watches; };
	const string& getLastViewed(void) { return lastViewed; };
	const string& getDateCreated(void) { return dateCreated; };
	const priority* getPriority(void) { return Priority; };
	const list<const string*>& getLabels(void) { return labels; };
	const string& getAggregrateOriginalEstimate(void) { return aggregrateOriginalEstimate; };
	const list<const string*>& getVersions(void) { return versions; };
	const list<link*>* getIssueLinks(void) { return issuelinks; };
	const string& getAssignee(void) { return assignee; };
	const string& getLastUpdated(void) { return lastUpdated; };
	const status& getStatus(void) { return status; };
	const string& getTimeOriginalEstimate(void) { return timeoriginalestimate; };
	const string& getDescription(void) { return description; };
	const string& Security(void) { return security; };
	const string& getSummary(void) { return summary; };
	const user* getCreator(void) { return creator; };
	const user& getReporter(void) { return reporter; };
	const progress& getAggregateProgress(void) { return aggregateProgress; };
	const string& getEnvironment(void) { return environment; };
	const string& getDueDate(void) { return dueDate; };
	const progress& getProgress(void) { return Progress; };

	void setStatusCategoryChangeDate(const string& _statuscategorychagedate) { statuscategorychangedate = _statuscategorychagedate; };
	void setIssueType(const issuetype& _issuetype) { Issuetype = _issuetype; };
	void setTimeSpent(const string& _timeSpent) { timeSpent = _timeSpent; };
	void setProject(const project& _project) { Project = _project; };
	void setFixVersions(list<const string*>& _fixVersions) { fixVersions = _fixVersions; };
	void setAggregateTimeSpent(const int _AggregateTimeSpent) { AggregateTimeSpent = _AggregateTimeSpent; };
	void setResolution(const string& _resolution) { resolution = _resolution; };
	void setResolutionDate(const string& _ResolutionDate) { resolutionDate = _ResolutionDate; };
	void setWorkRatio(const int _WorkRatio) { workRatio = _WorkRatio; };
	void setWatches(const watches& _watches) { Watches = _watches; };
	void setLastViewed(const string& _LastViewed) { lastViewed = _LastViewed; };
	void setDateCreated(const string& _DateCreated) { dateCreated = _DateCreated; };
	void setPriority(priority* _Priority) { Priority = _Priority; };
	void setLabels(const list<const string*>& _labels) { labels = _labels; };
	void setAggregrateOriginalEstimate(const string& _AggregateOriginalEstimate) { aggregrateOriginalEstimate = _AggregateOriginalEstimate; };
	void setVersions(list<const string*>& _Versions) { versions = _Versions; };
	void setIssueLinks(list<link*>* _IssueLinks) { issuelinks = _IssueLinks; };
	void setAssignee(const string& _Assignee) { assignee = _Assignee; };
	void setLastUpdated(const string& _lastUpdated) { lastUpdated = _lastUpdated; };
	void setStatus(const status& _status) { status = _status; };
	void setTimeOriginalEstimate(const string& _TimeOriginalEstimate) { timeoriginalestimate = _TimeOriginalEstimate; };
	void setDescription(const string& _description) { description = _description; };
	void setSecurity(const string& _security) { security = _security; };
	void setSummary(const string& _summary) { summary = _summary; };
	void setCreator(user* _creator) { creator = _creator; };
	void setReporter(const user& _reporter) { reporter = _reporter; };
	void setAggregateProgress(const progress& _aggregateProgress) { aggregateProgress = _aggregateProgress; };
	void setEnvironment(const string& _environment) { environment = environment; };
	void setDueDate(const string& _dueDate) { dueDate = _dueDate; };
	void setProgress(const progress& _Progress) { Progress = _Progress; };


	~fields() { issuelinks->clear(); delete issuelinks; delete creator; }

private:
	string statuscategorychangedate;
	issuetype Issuetype;
	string timeSpent;
	project Project;
	list<const string*> fixVersions;
	int AggregateTimeSpent;
	string resolution;
	string resolutionDate;
	int workRatio;
	watches Watches;
	string lastViewed;
	string dateCreated;
	priority* Priority;
	list<const string*>labels;
	string aggregrateOriginalEstimate;
	list<const string*> versions;
	list<link*>*issuelinks;
	string assignee;
	string lastUpdated;
	status status;
	string timeoriginalestimate;
	string description;
	string security;
	string summary;
	user* creator;
	user reporter;
	progress aggregateProgress;
	string environment;
	string dueDate;
	progress Progress;
};

class issue
{
public:
	const string& getId(void)const { return id; };
	const string& getSelf(void)const { return self; };
	const string& getKey(void)const { return key; };
	const changelog& getChangeLog(void) { return Changelog; };
	const fields& getFields(void) { return Fields; }

	void setId(const string& _id) { id = _id; }
	void setSelf(const string& _self) { self = _self; }
	void setKey(const string& _key) { key = _key; };
	void setChangeLog(const changelog& _Changelog) { Changelog = _Changelog; }
	void setFields(const fields& _fields) { Fields = _fields; }

	Status globalSetIssueField(const int FieldId, const string& updateString);
	Status globalSetIssueField(const int FieldId, const int updateInt);
	Status globalSetChangeLogField(const int FieldId, const string& updateString);

	Status globalSetIssueId(const string& updateIssue);
	Status globalSetIssueSelf (const string& updateIssue);
	Status globalSetIssueKey(const string& updateIssue);



private:
	string id;
	string self;
	string key;
	changelog Changelog;
	fields Fields;
};


class item
{
public:
	const string& getField(void)const { return field; };
	const string& getFieldType(void)const { return fieldtype; };
	const string& getFieldId(void)const { return field; };
	const string& getFrom(void)const { return from; };
	const string& getFromString(void)const { return fromString; };
	const string& getTo(void)const { return to; };
	const string& getToString(void)const { return toString; };

	void setField(const string& _field) { field = _field; }
	void setFieldType(const string& _fieldtype) { fieldtype = _fieldtype; }
	void setFieldId(const string& _fieldId) { fieldId = _fieldId; }
	void setFrom(const string& _from) { from = _from; }
	void setFromString(const string& _fromString) { fromString = _fromString; }
	void setTo(const string& _to) { to = _to; }
	void setToString(const string& _toString) { toString = _toString; }
	Status globalSetItemField(const int FieldId, const string& updateString);


private:
	string field;
	string fieldtype;
	string fieldId;
	string from;
	string fromString;
	string to;
	string toString;
};
