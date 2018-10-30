
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

// This source file was created by a code generator.
// Please do not edit.

#include "qpid/management/Manageable.h"
#include "qpid/management/Buffer.h"
#include "qpid/types/Variant.h"
#include "qpid/amqp_0_10/Codecs.h"
#include "qpid/management/ManagementAgent.h"
#include "Session.h"


#include "qpid/log/Statement.h"

#include <iostream>
#include <sstream>
#include <string.h>

using namespace qmf::org::apache::qpid::broker;
using           qpid::management::ManagementAgent;
using           qpid::management::Manageable;
using           qpid::management::ManagementObject;
using           qpid::management::Args;
using           qpid::management::Mutex;
using           std::string;

string  Session::packageName  = string ("org.apache.qpid.broker");
string  Session::className    = string ("session");
uint8_t Session::md5Sum[MD5_LEN]   =
    {0x3,0x38,0x2f,0xcb,0x66,0xf1,0x28,0xa,0xd6,0xcb,0x44,0x73,0x40,0xf6,0x3e,0xa3};

Session::Session (ManagementAgent*, Manageable* _core, ::qpid::management::Manageable* _parent, const std::string& _name) :
    ManagementObject(_core),name(_name)
{
    vhostRef = _parent->GetManagementObject()->getObjectId();
    fullName = "";
    channelId = 0;
    connectionRef = ::qpid::management::ObjectId();
    detachedLifespan = 0;
    attached = false;
    expireTime = 0;
    maxClientRate = 0;
    unackedMessages = 0;


    // Optional properties start out not-present
    for (uint8_t idx = 0; idx < 1; idx++)
        presenceMask[idx] = 0;


    perThreadStatsArray = new struct PerThreadStats*[maxThreads];
    for (int idx = 0; idx < maxThreads; idx++)
        perThreadStatsArray[idx] = 0;


    QPID_LOG_CAT(trace, model, "Mgmt create " << className
        << ". id:" << getKey());

}

Session::~Session ()
{

    for (int idx = 0; idx < maxThreads; idx++)
        if (perThreadStatsArray[idx] != 0)
            delete perThreadStatsArray[idx];
    delete[] perThreadStatsArray;

}

void Session::debugStats (const std::string& comment)
{

    bool logEnabled;
    QPID_LOG_TEST_CAT(trace, model, logEnabled);
    if (logEnabled)
    {
        ::qpid::types::Variant::Map map;
        mapEncodeValues(map, false, true);
        QPID_LOG_CAT(trace, model, "Mgmt " << comment << ((comment!="")?(" "):("")) << className
            << ". id:" << getKey()
            << " Statistics: " << map);
    }

}


namespace {
    const string NAME("name");
    const string TYPE("type");
    const string ACCESS("access");
    const string IS_INDEX("index");
    const string IS_OPTIONAL("optional");
    const string UNIT("unit");
    const string MIN("min");
    const string MAX("max");
    const string MAXLEN("maxlen");
    const string DESC("desc");
    const string ARGCOUNT("argCount");
    const string ARGS("args");
    const string DIR("dir");
    const string DEFAULT("default");
}

void Session::registerSelf(ManagementAgent* agent)
{
    agent->registerClass(packageName, className, md5Sum, writeSchema);
}

void Session::writeSchema (std::string& schema)
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer buf(_msgChars, _bufSize);
    ::qpid::types::Variant::Map ft;

    // Schema class header:
    buf.putOctet       (CLASS_KIND_TABLE);
    buf.putShortString (packageName); // Package Name
    buf.putShortString (className);   // Class Name
    buf.putBin128      (md5Sum);      // Schema Hash
    buf.putShort       (9); // Config Element Count
    buf.putShort       (7); // Inst Element Count
    buf.putShort       (4); // Method Count

    // Properties
    ft.clear();
    ft[NAME] = "vhostRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "name";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "fullName";
    ft[TYPE] = TYPE_LSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "channelId";
    ft[TYPE] = TYPE_U16;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "connectionRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "detachedLifespan";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[UNIT] = "second";
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "attached";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "expireTime";
    ft[TYPE] = TYPE_ABSTIME;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "maxClientRate";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    ft[UNIT] = "msgs/sec";
    ft[DESC] = "Deprecated";
    buf.putMap(ft);


    // Statistics
    ft.clear();
    ft[NAME] = "unackedMessages";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "message";
    ft[DESC] = "Unacknowledged messages in the session";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "TxnStarts";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "transaction";
    ft[DESC] = "Total transactions started ";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "TxnCommits";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "transaction";
    ft[DESC] = "Total transactions committed";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "TxnRejects";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "transaction";
    ft[DESC] = "Total transactions rejected";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "TxnCount";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "transaction";
    ft[DESC] = "Current pending transactions";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "clientCredit";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "message";
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "framesOutstanding";
    ft[TYPE] = TYPE_U32;
    ft[DESC] = "Deprecated";
    buf.putMap(ft);


    // Methods
    ft.clear();
    ft[NAME] =  "solicitAck";
    ft[ARGCOUNT] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] =  "detach";
    ft[ARGCOUNT] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] =  "resetLifespan";
    ft[ARGCOUNT] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] =  "close";
    ft[ARGCOUNT] = 0;
    buf.putMap(ft);


    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}


void Session::aggregatePerThreadStats(struct PerThreadStats* totals) const
{
    totals->TxnStarts = 0;
    totals->TxnCommits = 0;
    totals->TxnRejects = 0;
    totals->TxnCount = 0;
    totals->clientCredit = 0;
    totals->framesOutstanding = 0;

    for (int idx = 0; idx < maxThreads; idx++) {
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats != 0) {
            totals->TxnStarts += threadStats->TxnStarts;
            totals->TxnCommits += threadStats->TxnCommits;
            totals->TxnRejects += threadStats->TxnRejects;
            totals->TxnCount += threadStats->TxnCount;
            totals->clientCredit += threadStats->clientCredit;
            totals->framesOutstanding += threadStats->framesOutstanding;

        }
    }
}



uint32_t Session::writePropertiesSize() const
{
    uint32_t size = writeTimestampsSize();

    size += 1;

    size += 16;  // vhostRef
    size += (1 + name.length());  // name
    if (presenceMask[presenceByte_fullName] & presenceMask_fullName) {
        size += (2 + fullName.length());  // fullName
    }
    size += 2;  // channelId
    size += 16;  // connectionRef
    size += 4;  // detachedLifespan
    size += 1;  // attached
    if (presenceMask[presenceByte_expireTime] & presenceMask_expireTime) {
        size += 8;  // expireTime
    }
    if (presenceMask[presenceByte_maxClientRate] & presenceMask_maxClientRate) {
        size += 4;  // maxClientRate
    }

    return size;
}

void Session::readProperties (const std::string& _sBuf)
{
    char *_tmpBuf = new char[_sBuf.length()];
    memcpy(_tmpBuf, _sBuf.data(), _sBuf.length());
    ::qpid::management::Buffer buf(_tmpBuf, _sBuf.length());
    Mutex::ScopedLock mutex(accessLock);

    {
        std::string _tbuf;
        buf.getRawData(_tbuf, writeTimestampsSize());
        readTimestamps(_tbuf);
    }


    for (uint8_t idx = 0; idx < 1; idx++)
        presenceMask[idx] = buf.getOctet();

    {std::string _s; buf.getRawData(_s, vhostRef.encodedSize()); vhostRef.decode(_s);};
    buf.getShortString(name);
    if (presenceMask[presenceByte_fullName] & presenceMask_fullName) {
        buf.getMediumString(fullName);
    }
    channelId = buf.getShort();
    {std::string _s; buf.getRawData(_s, connectionRef.encodedSize()); connectionRef.decode(_s);};
    detachedLifespan = buf.getLong();
    attached = buf.getOctet()==1;
    if (presenceMask[presenceByte_expireTime] & presenceMask_expireTime) {
        expireTime = buf.getLongLong();
    }
    if (presenceMask[presenceByte_maxClientRate] & presenceMask_maxClientRate) {
        maxClientRate = buf.getLong();
    }


    delete [] _tmpBuf;
}

void Session::writeProperties (std::string& _sBuf) const
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer buf(_msgChars, _bufSize);

    Mutex::ScopedLock mutex(accessLock);
    configChanged = false;

    {
        std::string _tbuf;
        writeTimestamps(_tbuf);
        buf.putRawData(_tbuf);
    }



    for (uint8_t idx = 0; idx < 1; idx++)
        buf.putOctet(presenceMask[idx]);

    {std::string _s; vhostRef.encode(_s); buf.putRawData(_s);};
    buf.putShortString(name);
    if (presenceMask[presenceByte_fullName] & presenceMask_fullName) {
        buf.putMediumString(fullName);
    }
    buf.putShort(channelId);
    {std::string _s; connectionRef.encode(_s); buf.putRawData(_s);};
    buf.putLong(detachedLifespan);
    buf.putOctet(attached?1:0);
    if (presenceMask[presenceByte_expireTime] & presenceMask_expireTime) {
        buf.putLongLong(expireTime);
    }
    if (presenceMask[presenceByte_maxClientRate] & presenceMask_maxClientRate) {
        buf.putLong(maxClientRate);
    }


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Session::writeStatistics (std::string& _sBuf, bool skipHeaders)
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer buf(_msgChars, _bufSize);

    Mutex::ScopedLock mutex(accessLock);
    instChanged = false;


    struct PerThreadStats totals;
    aggregatePerThreadStats(&totals);


    if (!skipHeaders) {
        std::string _tbuf;
        writeTimestamps (_tbuf);
        buf.putRawData(_tbuf);
    }

    buf.putLongLong(unackedMessages);
    buf.putLongLong(totals.TxnStarts);
    buf.putLongLong(totals.TxnCommits);
    buf.putLongLong(totals.TxnRejects);
    buf.putLong(totals.TxnCount);
    buf.putLong(totals.clientCredit);
    buf.putLong(totals.framesOutstanding);


    // Maintenance of hi-lo statistics



    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Session::doMethod (string& methodName, const string&, string& outStr, const string& userId)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;

    bool _matched = false;

    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer outBuf(_msgChars, _bufSize);


    if (methodName == "solicitAck") {
        _matched = true;
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_SOLICITACK, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_SOLICITACK, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outBuf.putLong        (status);
        outBuf.putMediumString(::qpid::management::Manageable::StatusText (status, text));
    }

    if (methodName == "detach") {
        _matched = true;
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_DETACH, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_DETACH, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outBuf.putLong        (status);
        outBuf.putMediumString(::qpid::management::Manageable::StatusText (status, text));
    }

    if (methodName == "resetLifespan") {
        _matched = true;
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_RESETLIFESPAN, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_RESETLIFESPAN, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outBuf.putLong        (status);
        outBuf.putMediumString(::qpid::management::Manageable::StatusText (status, text));
    }

    if (methodName == "close") {
        _matched = true;
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_CLOSE, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_CLOSE, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outBuf.putLong        (status);
        outBuf.putMediumString(::qpid::management::Manageable::StatusText (status, text));
    }


    if (!_matched) {
        outBuf.putLong(status);
        outBuf.putShortString(Manageable::StatusText(status, text));
    }

    uint32_t _bufLen = outBuf.getPosition();
    outBuf.reset();

    outBuf.getRawData(outStr, _bufLen);
}

std::string Session::getKey() const
{
    std::stringstream key;

    key << name;
    return key.str();
}


void Session::mapEncodeValues (::qpid::types::Variant::Map& _map,
                                              bool includeProperties,
                                              bool includeStatistics)
{
    using namespace ::qpid::types;
    Mutex::ScopedLock mutex(accessLock);

    if (includeProperties) {
        configChanged = false;
    _map["vhostRef"] = ::qpid::types::Variant(vhostRef);
    _map["name"] = ::qpid::types::Variant(name);
    if (presenceMask[presenceByte_fullName] & presenceMask_fullName) {
        _map["fullName"] = ::qpid::types::Variant(fullName);
    }
    _map["channelId"] = ::qpid::types::Variant(channelId);
    _map["connectionRef"] = ::qpid::types::Variant(connectionRef);
    _map["detachedLifespan"] = ::qpid::types::Variant(detachedLifespan);
    _map["attached"] = ::qpid::types::Variant(attached);
    if (presenceMask[presenceByte_expireTime] & presenceMask_expireTime) {
        _map["expireTime"] = ::qpid::types::Variant(expireTime);
    }
    if (presenceMask[presenceByte_maxClientRate] & presenceMask_maxClientRate) {
        _map["maxClientRate"] = ::qpid::types::Variant(maxClientRate);
    }

    }

    if (includeStatistics) {
        instChanged = false;


        struct PerThreadStats totals;
        aggregatePerThreadStats(&totals);



    _map["unackedMessages"] = ::qpid::types::Variant(unackedMessages);
    _map["TxnStarts"] = ::qpid::types::Variant(totals.TxnStarts);
    _map["TxnCommits"] = ::qpid::types::Variant(totals.TxnCommits);
    _map["TxnRejects"] = ::qpid::types::Variant(totals.TxnRejects);
    _map["TxnCount"] = ::qpid::types::Variant(totals.TxnCount);
    _map["clientCredit"] = ::qpid::types::Variant(totals.clientCredit);
    _map["framesOutstanding"] = ::qpid::types::Variant(totals.framesOutstanding);


    // Maintenance of hi-lo statistics


    }
}

void Session::mapDecodeValues (const ::qpid::types::Variant::Map& _map)
{
    ::qpid::types::Variant::Map::const_iterator _i;
    Mutex::ScopedLock mutex(accessLock);

    bool _found;

    if ((_i = _map.find("vhostRef")) != _map.end()) {
        vhostRef = _i->second;
    } else {
        vhostRef = ::qpid::management::ObjectId();
    }
    if ((_i = _map.find("name")) != _map.end()) {
        name = (_i->second).getString();
    } else {
        name = "";
    }
    _found = false;
    if ((_i = _map.find("fullName")) != _map.end()) {
        fullName = (_i->second).getString();
        _found = true;
    } else {
        fullName = "";
    }
    if (_found) {
        presenceMask[presenceByte_fullName] |= presenceMask_fullName;
    }
    if ((_i = _map.find("channelId")) != _map.end()) {
        channelId = _i->second;
    } else {
        channelId = 0;
    }
    if ((_i = _map.find("connectionRef")) != _map.end()) {
        connectionRef = _i->second;
    } else {
        connectionRef = ::qpid::management::ObjectId();
    }
    if ((_i = _map.find("detachedLifespan")) != _map.end()) {
        detachedLifespan = _i->second;
    } else {
        detachedLifespan = 0;
    }
    if ((_i = _map.find("attached")) != _map.end()) {
        attached = _i->second;
    } else {
        attached = false;
    }
    _found = false;
    if ((_i = _map.find("expireTime")) != _map.end()) {
        expireTime = _i->second;
        _found = true;
    } else {
        expireTime = 0;
    }
    if (_found) {
        presenceMask[presenceByte_expireTime] |= presenceMask_expireTime;
    }
    _found = false;
    if ((_i = _map.find("maxClientRate")) != _map.end()) {
        maxClientRate = _i->second;
        _found = true;
    } else {
        maxClientRate = 0;
    }
    if (_found) {
        presenceMask[presenceByte_maxClientRate] |= presenceMask_maxClientRate;
    }

}

void Session::doMethod (string& methodName, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string& userId)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;


    if (methodName == "solicitAck") {
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_SOLICITACK, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_SOLICITACK, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outMap["_status_code"] = (uint32_t) status;
        outMap["_status_text"] = ::qpid::management::Manageable::StatusText(status, text);
        return;
    }

    if (methodName == "detach") {
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_DETACH, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_DETACH, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outMap["_status_code"] = (uint32_t) status;
        outMap["_status_text"] = ::qpid::management::Manageable::StatusText(status, text);
        return;
    }

    if (methodName == "resetLifespan") {
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_RESETLIFESPAN, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_RESETLIFESPAN, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outMap["_status_code"] = (uint32_t) status;
        outMap["_status_text"] = ::qpid::management::Manageable::StatusText(status, text);
        return;
    }

    if (methodName == "close") {
        ::qpid::management::ArgsNone ioArgs;
        bool allow = manageable.AuthorizeMethod(METHOD_CLOSE, ioArgs, userId);
        if (allow)
            status = manageable.ManagementMethod (METHOD_CLOSE, ioArgs, text);
        else
            status = Manageable::STATUS_FORBIDDEN;
        outMap["_status_code"] = (uint32_t) status;
        outMap["_status_text"] = ::qpid::management::Manageable::StatusText(status, text);
        return;
    }

    outMap["_status_code"] = (uint32_t) status;
    outMap["_status_text"] = Manageable::StatusText(status, text);
}
