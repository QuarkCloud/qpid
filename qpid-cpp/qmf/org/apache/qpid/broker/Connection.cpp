
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
#include "Connection.h"


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

string  Connection::packageName  = string ("org.apache.qpid.broker");
string  Connection::className    = string ("connection");
uint8_t Connection::md5Sum[MD5_LEN]   =
    {0x99,0xb8,0x1a,0xdb,0x2c,0xf6,0x6,0xa7,0xac,0x90,0x1c,0xb4,0x2e,0x67,0xc2,0xfc};

Connection::Connection (ManagementAgent*, Manageable* _core, ::qpid::management::Manageable* _parent, const std::string& _address, bool _incoming, bool _SystemConnection, const std::string& _protocol) :
    ManagementObject(_core),address(_address),incoming(_incoming),SystemConnection(_SystemConnection),protocol(_protocol)
{
    vhostRef = _parent->GetManagementObject()->getObjectId();
    userProxyAuth = false;
    federationLink = false;
    authIdentity = "";
    remoteProcessName = "";
    remotePid = 0;
    remoteParentPid = 0;
    shadow = false;
    saslMechanism = "";
    saslSsf = 0;
    remoteProperties = ::qpid::types::Variant::Map();
    closing = false;


    // Optional properties start out not-present
    for (uint8_t idx = 0; idx < 1; idx++)
        presenceMask[idx] = 0;


    perThreadStatsArray = new struct PerThreadStats*[maxThreads];
    for (int idx = 0; idx < maxThreads; idx++)
        perThreadStatsArray[idx] = 0;


    QPID_LOG_CAT(trace, model, "Mgmt create " << className
        << ". id:" << getKey());

}

Connection::~Connection ()
{

    for (int idx = 0; idx < maxThreads; idx++)
        if (perThreadStatsArray[idx] != 0)
            delete perThreadStatsArray[idx];
    delete[] perThreadStatsArray;

}

void Connection::debugStats (const std::string& comment)
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

void Connection::registerSelf(ManagementAgent* agent)
{
    agent->registerClass(packageName, className, md5Sum, writeSchema);
}

void Connection::writeSchema (std::string& schema)
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
    buf.putShort       (15); // Config Element Count
    buf.putShort       (7); // Inst Element Count
    buf.putShort       (1); // Method Count

    // Properties
    ft.clear();
    ft[NAME] = "vhostRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "address";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "incoming";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "SystemConnection";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "userProxyAuth";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "federationLink";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "authIdentity";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "authId of connection if authentication enabled";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "remoteProcessName";
    ft[TYPE] = TYPE_LSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    ft[DESC] = "Name of executable running as remote client";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "remotePid";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    ft[DESC] = "Process ID of remote client";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "remoteParentPid";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 1;
    ft[DESC] = "Parent Process ID of remote client";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "shadow";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "saslMechanism";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "SASL mechanism";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "saslSsf";
    ft[TYPE] = TYPE_U16;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "SASL security strength factor";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "remoteProperties";
    ft[TYPE] = TYPE_FTABLE;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "optional map of identifying information sent by the remote";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "protocol";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "protocol in use";
    buf.putMap(ft);


    // Statistics
    ft.clear();
    ft[NAME] = "closing";
    ft[TYPE] = TYPE_BOOL;
    ft[DESC] = "This client is closing by management request";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "framesFromClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "framesToClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "bytesFromClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "bytesToClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "msgsFromClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "msgsToClient";
    ft[TYPE] = TYPE_U64;
    buf.putMap(ft);


    // Methods
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


void Connection::aggregatePerThreadStats(struct PerThreadStats* totals) const
{
    totals->framesFromClient = 0;
    totals->framesToClient = 0;
    totals->bytesFromClient = 0;
    totals->bytesToClient = 0;
    totals->msgsFromClient = 0;
    totals->msgsToClient = 0;

    for (int idx = 0; idx < maxThreads; idx++) {
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats != 0) {
            totals->framesFromClient += threadStats->framesFromClient;
            totals->framesToClient += threadStats->framesToClient;
            totals->bytesFromClient += threadStats->bytesFromClient;
            totals->bytesToClient += threadStats->bytesToClient;
            totals->msgsFromClient += threadStats->msgsFromClient;
            totals->msgsToClient += threadStats->msgsToClient;

        }
    }
}



uint32_t Connection::writePropertiesSize() const
{
    uint32_t size = writeTimestampsSize();

    size += 1;

    size += 16;  // vhostRef
    size += (1 + address.length());  // address
    size += 1;  // incoming
    size += 1;  // SystemConnection
    size += 1;  // userProxyAuth
    size += 1;  // federationLink
    size += (1 + authIdentity.length());  // authIdentity
    if (presenceMask[presenceByte_remoteProcessName] & presenceMask_remoteProcessName) {
        size += (2 + remoteProcessName.length());  // remoteProcessName
    }
    if (presenceMask[presenceByte_remotePid] & presenceMask_remotePid) {
        size += 4;  // remotePid
    }
    if (presenceMask[presenceByte_remoteParentPid] & presenceMask_remoteParentPid) {
        size += 4;  // remoteParentPid
    }
    size += 1;  // shadow
    size += (1 + saslMechanism.length());  // saslMechanism
    size += 2;  // saslSsf
    size += ::qpid::amqp_0_10::MapCodec::encodedSize(remoteProperties);  // remoteProperties
    size += (1 + protocol.length());  // protocol

    return size;
}

void Connection::readProperties (const std::string& _sBuf)
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
    buf.getShortString(address);
    incoming = buf.getOctet()==1;
    SystemConnection = buf.getOctet()==1;
    userProxyAuth = buf.getOctet()==1;
    federationLink = buf.getOctet()==1;
    buf.getShortString(authIdentity);
    if (presenceMask[presenceByte_remoteProcessName] & presenceMask_remoteProcessName) {
        buf.getMediumString(remoteProcessName);
    }
    if (presenceMask[presenceByte_remotePid] & presenceMask_remotePid) {
        remotePid = buf.getLong();
    }
    if (presenceMask[presenceByte_remoteParentPid] & presenceMask_remoteParentPid) {
        remoteParentPid = buf.getLong();
    }
    shadow = buf.getOctet()==1;
    buf.getShortString(saslMechanism);
    saslSsf = buf.getShort();
    buf.getMap(remoteProperties);
    buf.getShortString(protocol);


    delete [] _tmpBuf;
}

void Connection::writeProperties (std::string& _sBuf) const
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
    buf.putShortString(address);
    buf.putOctet(incoming?1:0);
    buf.putOctet(SystemConnection?1:0);
    buf.putOctet(userProxyAuth?1:0);
    buf.putOctet(federationLink?1:0);
    buf.putShortString(authIdentity);
    if (presenceMask[presenceByte_remoteProcessName] & presenceMask_remoteProcessName) {
        buf.putMediumString(remoteProcessName);
    }
    if (presenceMask[presenceByte_remotePid] & presenceMask_remotePid) {
        buf.putLong(remotePid);
    }
    if (presenceMask[presenceByte_remoteParentPid] & presenceMask_remoteParentPid) {
        buf.putLong(remoteParentPid);
    }
    buf.putOctet(shadow?1:0);
    buf.putShortString(saslMechanism);
    buf.putShort(saslSsf);
    buf.putMap(remoteProperties);
    buf.putShortString(protocol);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Connection::writeStatistics (std::string& _sBuf, bool skipHeaders)
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

    buf.putOctet(closing?1:0);
    buf.putLongLong(totals.framesFromClient);
    buf.putLongLong(totals.framesToClient);
    buf.putLongLong(totals.bytesFromClient);
    buf.putLongLong(totals.bytesToClient);
    buf.putLongLong(totals.msgsFromClient);
    buf.putLongLong(totals.msgsToClient);


    // Maintenance of hi-lo statistics



    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Connection::doMethod (string& methodName, const string&, string& outStr, const string& userId)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;

    bool _matched = false;

    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer outBuf(_msgChars, _bufSize);


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

std::string Connection::getKey() const
{
    std::stringstream key;

    key << address;
    return key.str();
}


void Connection::mapEncodeValues (::qpid::types::Variant::Map& _map,
                                              bool includeProperties,
                                              bool includeStatistics)
{
    using namespace ::qpid::types;
    Mutex::ScopedLock mutex(accessLock);

    if (includeProperties) {
        configChanged = false;
    _map["vhostRef"] = ::qpid::types::Variant(vhostRef);
    _map["address"] = ::qpid::types::Variant(address);
    _map["incoming"] = ::qpid::types::Variant(incoming);
    _map["SystemConnection"] = ::qpid::types::Variant(SystemConnection);
    _map["userProxyAuth"] = ::qpid::types::Variant(userProxyAuth);
    _map["federationLink"] = ::qpid::types::Variant(federationLink);
    _map["authIdentity"] = ::qpid::types::Variant(authIdentity);
    if (presenceMask[presenceByte_remoteProcessName] & presenceMask_remoteProcessName) {
        _map["remoteProcessName"] = ::qpid::types::Variant(remoteProcessName);
    }
    if (presenceMask[presenceByte_remotePid] & presenceMask_remotePid) {
        _map["remotePid"] = ::qpid::types::Variant(remotePid);
    }
    if (presenceMask[presenceByte_remoteParentPid] & presenceMask_remoteParentPid) {
        _map["remoteParentPid"] = ::qpid::types::Variant(remoteParentPid);
    }
    _map["shadow"] = ::qpid::types::Variant(shadow);
    _map["saslMechanism"] = ::qpid::types::Variant(saslMechanism);
    _map["saslSsf"] = ::qpid::types::Variant(saslSsf);
    _map["remoteProperties"] = ::qpid::types::Variant(remoteProperties);
    _map["protocol"] = ::qpid::types::Variant(protocol);

    }

    if (includeStatistics) {
        instChanged = false;


        struct PerThreadStats totals;
        aggregatePerThreadStats(&totals);



    _map["closing"] = ::qpid::types::Variant(closing);
    _map["framesFromClient"] = ::qpid::types::Variant(totals.framesFromClient);
    _map["framesToClient"] = ::qpid::types::Variant(totals.framesToClient);
    _map["bytesFromClient"] = ::qpid::types::Variant(totals.bytesFromClient);
    _map["bytesToClient"] = ::qpid::types::Variant(totals.bytesToClient);
    _map["msgsFromClient"] = ::qpid::types::Variant(totals.msgsFromClient);
    _map["msgsToClient"] = ::qpid::types::Variant(totals.msgsToClient);


    // Maintenance of hi-lo statistics


    }
}

void Connection::mapDecodeValues (const ::qpid::types::Variant::Map& _map)
{
    ::qpid::types::Variant::Map::const_iterator _i;
    Mutex::ScopedLock mutex(accessLock);

    bool _found;

    if ((_i = _map.find("vhostRef")) != _map.end()) {
        vhostRef = _i->second;
    } else {
        vhostRef = ::qpid::management::ObjectId();
    }
    if ((_i = _map.find("address")) != _map.end()) {
        address = (_i->second).getString();
    } else {
        address = "";
    }
    if ((_i = _map.find("incoming")) != _map.end()) {
        incoming = _i->second;
    } else {
        incoming = false;
    }
    if ((_i = _map.find("SystemConnection")) != _map.end()) {
        SystemConnection = _i->second;
    } else {
        SystemConnection = false;
    }
    if ((_i = _map.find("userProxyAuth")) != _map.end()) {
        userProxyAuth = _i->second;
    } else {
        userProxyAuth = false;
    }
    if ((_i = _map.find("federationLink")) != _map.end()) {
        federationLink = _i->second;
    } else {
        federationLink = false;
    }
    if ((_i = _map.find("authIdentity")) != _map.end()) {
        authIdentity = (_i->second).getString();
    } else {
        authIdentity = "";
    }
    _found = false;
    if ((_i = _map.find("remoteProcessName")) != _map.end()) {
        remoteProcessName = (_i->second).getString();
        _found = true;
    } else {
        remoteProcessName = "";
    }
    if (_found) {
        presenceMask[presenceByte_remoteProcessName] |= presenceMask_remoteProcessName;
    }
    _found = false;
    if ((_i = _map.find("remotePid")) != _map.end()) {
        remotePid = _i->second;
        _found = true;
    } else {
        remotePid = 0;
    }
    if (_found) {
        presenceMask[presenceByte_remotePid] |= presenceMask_remotePid;
    }
    _found = false;
    if ((_i = _map.find("remoteParentPid")) != _map.end()) {
        remoteParentPid = _i->second;
        _found = true;
    } else {
        remoteParentPid = 0;
    }
    if (_found) {
        presenceMask[presenceByte_remoteParentPid] |= presenceMask_remoteParentPid;
    }
    if ((_i = _map.find("shadow")) != _map.end()) {
        shadow = _i->second;
    } else {
        shadow = false;
    }
    if ((_i = _map.find("saslMechanism")) != _map.end()) {
        saslMechanism = (_i->second).getString();
    } else {
        saslMechanism = "";
    }
    if ((_i = _map.find("saslSsf")) != _map.end()) {
        saslSsf = _i->second;
    } else {
        saslSsf = 0;
    }
    if ((_i = _map.find("remoteProperties")) != _map.end()) {
        remoteProperties = (_i->second).asMap();
    } else {
        remoteProperties = ::qpid::types::Variant::Map();
    }
    if ((_i = _map.find("protocol")) != _map.end()) {
        protocol = (_i->second).getString();
    } else {
        protocol = "";
    }

}

void Connection::doMethod (string& methodName, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string& userId)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;


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
