
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
#include "Store.h"


#include "qpid/log/Statement.h"

#include <iostream>
#include <sstream>
#include <string.h>

using namespace qmf::org::apache::qpid::linearstore;
using           qpid::management::ManagementAgent;
using           qpid::management::Manageable;
using           qpid::management::ManagementObject;
using           qpid::management::Args;
using           qpid::management::Mutex;
using           std::string;

string  Store::packageName  = string ("org.apache.qpid.linearstore");
string  Store::className    = string ("store");
uint8_t Store::md5Sum[MD5_LEN]   =
    {0x67,0x1e,0x55,0x21,0xc3,0xc1,0xed,0x29,0x2f,0xd4,0x10,0xd5,0x7,0xa0,0xef,0x8f};

Store::Store (ManagementAgent*, Manageable* _core, ::qpid::management::Manageable* _parent) :
    ManagementObject(_core)
{
    brokerRef = _parent->GetManagementObject()->getObjectId();
    storeDir = "";
    tplIsInitialized = false;
    tplDirectory = "";
    tplWritePageSize = 0;
    tplWritePages = 0;
    tplTransactionDepth = 0;
    tplTransactionDepthHigh = 0;
    tplTransactionDepthLow  = 0;



    perThreadStatsArray = new struct PerThreadStats*[maxThreads];
    for (int idx = 0; idx < maxThreads; idx++)
        perThreadStatsArray[idx] = 0;


    QPID_LOG_CAT(trace, model, "Mgmt create " << className
        << ". id:" << getKey());

}

Store::~Store ()
{

    for (int idx = 0; idx < maxThreads; idx++)
        if (perThreadStatsArray[idx] != 0)
            delete perThreadStatsArray[idx];
    delete[] perThreadStatsArray;

}

void Store::debugStats (const std::string& comment)
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

void Store::registerSelf(ManagementAgent* agent)
{
    agent->registerClass(packageName, className, md5Sum, writeSchema);
}

void Store::writeSchema (std::string& schema)
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
    buf.putShort       (6); // Config Element Count
    buf.putShort       (6); // Inst Element Count
    buf.putShort       (0); // Method Count

    // Properties
    ft.clear();
    ft[NAME] = "brokerRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "storeDir";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Logical directory on disk";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplIsInitialized";
    ft[TYPE] = TYPE_BOOL;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Transaction prepared list has been initialized by a transactional prepare";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplDirectory";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Transaction prepared list directory";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplWritePageSize";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[UNIT] = "byte";
    ft[DESC] = "Page size in transaction prepared list write-page-cache";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplWritePages";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[UNIT] = "wpage";
    ft[DESC] = "Number of pages in transaction prepared list write-page-cache";
    buf.putMap(ft);


    // Statistics
    ft.clear();
    ft[NAME] = "tplTransactionDepth";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "txn";
    ft[DESC] = "Number of currently enqueued prepared transactions";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplTransactionDepthHigh";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "txn";
    ft[DESC] = "Number of currently enqueued prepared transactions (High)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplTransactionDepthLow";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "txn";
    ft[DESC] = "Number of currently enqueued prepared transactions (Low)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplTxnPrepares";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transaction prepares on transaction prepared list";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplTxnCommits";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transaction commits on transaction prepared list";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "tplTxnAborts";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transaction aborts on transaction prepared list";
    buf.putMap(ft);


    // Methods

    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}


void Store::aggregatePerThreadStats(struct PerThreadStats* totals) const
{
    totals->tplTxnPrepares = 0;
    totals->tplTxnCommits = 0;
    totals->tplTxnAborts = 0;

    for (int idx = 0; idx < maxThreads; idx++) {
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats != 0) {
            totals->tplTxnPrepares += threadStats->tplTxnPrepares;
            totals->tplTxnCommits += threadStats->tplTxnCommits;
            totals->tplTxnAborts += threadStats->tplTxnAborts;

        }
    }
}



uint32_t Store::writePropertiesSize() const
{
    uint32_t size = writeTimestampsSize();

    size += 16;  // brokerRef
    size += (1 + storeDir.length());  // storeDir
    size += 1;  // tplIsInitialized
    size += (1 + tplDirectory.length());  // tplDirectory
    size += 4;  // tplWritePageSize
    size += 4;  // tplWritePages

    return size;
}

void Store::readProperties (const std::string& _sBuf)
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


    {std::string _s; buf.getRawData(_s, brokerRef.encodedSize()); brokerRef.decode(_s);};
    buf.getShortString(storeDir);
    tplIsInitialized = buf.getOctet()==1;
    buf.getShortString(tplDirectory);
    tplWritePageSize = buf.getLong();
    tplWritePages = buf.getLong();


    delete [] _tmpBuf;
}

void Store::writeProperties (std::string& _sBuf) const
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



    {std::string _s; brokerRef.encode(_s); buf.putRawData(_s);};
    buf.putShortString(storeDir);
    buf.putOctet(tplIsInitialized?1:0);
    buf.putShortString(tplDirectory);
    buf.putLong(tplWritePageSize);
    buf.putLong(tplWritePages);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Store::writeStatistics (std::string& _sBuf, bool skipHeaders)
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

    buf.putLong(tplTransactionDepth);
    buf.putLong(tplTransactionDepthHigh);
    buf.putLong(tplTransactionDepthLow);
    buf.putLongLong(totals.tplTxnPrepares);
    buf.putLongLong(totals.tplTxnCommits);
    buf.putLongLong(totals.tplTxnAborts);


    // Maintenance of hi-lo statistics
    tplTransactionDepthHigh = tplTransactionDepth;
    tplTransactionDepthLow  = tplTransactionDepth;



    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Store::doMethod (string&, const string&, string& outStr, const string&)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;

    bool _matched = false;

    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer outBuf(_msgChars, _bufSize);



    if (!_matched) {
        outBuf.putLong(status);
        outBuf.putShortString(Manageable::StatusText(status, text));
    }

    uint32_t _bufLen = outBuf.getPosition();
    outBuf.reset();

    outBuf.getRawData(outStr, _bufLen);
}

std::string Store::getKey() const
{
    std::stringstream key;

    key << brokerRef.getV2Key();
    return key.str();
}


void Store::mapEncodeValues (::qpid::types::Variant::Map& _map,
                                              bool includeProperties,
                                              bool includeStatistics)
{
    using namespace ::qpid::types;
    Mutex::ScopedLock mutex(accessLock);

    if (includeProperties) {
        configChanged = false;
    _map["brokerRef"] = ::qpid::types::Variant(brokerRef);
    _map["storeDir"] = ::qpid::types::Variant(storeDir);
    _map["tplIsInitialized"] = ::qpid::types::Variant(tplIsInitialized);
    _map["tplDirectory"] = ::qpid::types::Variant(tplDirectory);
    _map["tplWritePageSize"] = ::qpid::types::Variant(tplWritePageSize);
    _map["tplWritePages"] = ::qpid::types::Variant(tplWritePages);

    }

    if (includeStatistics) {
        instChanged = false;


        struct PerThreadStats totals;
        aggregatePerThreadStats(&totals);



    _map["tplTransactionDepth"] = ::qpid::types::Variant(tplTransactionDepth);
    _map["tplTransactionDepthHigh"] = ::qpid::types::Variant(tplTransactionDepthHigh);
    _map["tplTransactionDepthLow"] = ::qpid::types::Variant(tplTransactionDepthLow);
    _map["tplTxnPrepares"] = ::qpid::types::Variant(totals.tplTxnPrepares);
    _map["tplTxnCommits"] = ::qpid::types::Variant(totals.tplTxnCommits);
    _map["tplTxnAborts"] = ::qpid::types::Variant(totals.tplTxnAborts);


    // Maintenance of hi-lo statistics
    tplTransactionDepthHigh = tplTransactionDepth;
    tplTransactionDepthLow  = tplTransactionDepth;


    }
}

void Store::mapDecodeValues (const ::qpid::types::Variant::Map& _map)
{
    ::qpid::types::Variant::Map::const_iterator _i;
    Mutex::ScopedLock mutex(accessLock);

    if ((_i = _map.find("brokerRef")) != _map.end()) {
        brokerRef = _i->second;
    } else {
        brokerRef = ::qpid::management::ObjectId();
    }
    if ((_i = _map.find("storeDir")) != _map.end()) {
        storeDir = (_i->second).getString();
    } else {
        storeDir = "";
    }
    if ((_i = _map.find("tplIsInitialized")) != _map.end()) {
        tplIsInitialized = _i->second;
    } else {
        tplIsInitialized = false;
    }
    if ((_i = _map.find("tplDirectory")) != _map.end()) {
        tplDirectory = (_i->second).getString();
    } else {
        tplDirectory = "";
    }
    if ((_i = _map.find("tplWritePageSize")) != _map.end()) {
        tplWritePageSize = _i->second;
    } else {
        tplWritePageSize = 0;
    }
    if ((_i = _map.find("tplWritePages")) != _map.end()) {
        tplWritePages = _i->second;
    } else {
        tplWritePages = 0;
    }

}

void Store::doMethod (string&, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string&)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;


    outMap["_status_code"] = (uint32_t) status;
    outMap["_status_text"] = Manageable::StatusText(status, text);
}
