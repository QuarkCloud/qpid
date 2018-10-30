
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
#include "Journal.h"


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

string  Journal::packageName  = string ("org.apache.qpid.linearstore");
string  Journal::className    = string ("journal");
uint8_t Journal::md5Sum[MD5_LEN]   =
    {0x4,0xf7,0xbe,0x8d,0x95,0xf8,0xd5,0xa4,0xf5,0x90,0x29,0xe3,0x28,0xac,0x90,0xf};

Journal::Journal (ManagementAgent*, Manageable* _core, const std::string& _queueName) :
    ManagementObject(_core),queueName(_queueName)
{
    
    queueRef = ::qpid::management::ObjectId();
    directory = "";
    writePageSize = 0;
    writePages = 0;
    recordDepth = 0;
    recordDepthHigh = 0;
    recordDepthLow  = 0;
    outstandingAIOs = 0;
    outstandingAIOsHigh = 0;
    outstandingAIOsLow  = 0;



    perThreadStatsArray = new struct PerThreadStats*[maxThreads];
    for (int idx = 0; idx < maxThreads; idx++)
        perThreadStatsArray[idx] = 0;


    QPID_LOG_CAT(trace, model, "Mgmt create " << className
        << ". id:" << getKey());

}

Journal::~Journal ()
{

    for (int idx = 0; idx < maxThreads; idx++)
        if (perThreadStatsArray[idx] != 0)
            delete perThreadStatsArray[idx];
    delete[] perThreadStatsArray;

}

void Journal::debugStats (const std::string& comment)
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

void Journal::registerSelf(ManagementAgent* agent)
{
    agent->registerClass(packageName, className, md5Sum, writeSchema);
}

void Journal::writeSchema (std::string& schema)
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
    buf.putShort       (5); // Config Element Count
    buf.putShort       (13); // Inst Element Count
    buf.putShort       (0); // Method Count

    // Properties
    ft.clear();
    ft[NAME] = "queueRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "queueName";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "directory";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[DESC] = "Directory containing journal files";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "writePageSize";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[UNIT] = "byte";
    ft[DESC] = "Deprecated";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "writePages";
    ft[TYPE] = TYPE_U32;
    ft[ACCESS] = ACCESS_RO;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    ft[UNIT] = "wpage";
    ft[DESC] = "Deprecated";
    buf.putMap(ft);


    // Statistics
    ft.clear();
    ft[NAME] = "recordDepth";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "record";
    ft[DESC] = "Number of currently enqueued records (durable messages)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "recordDepthHigh";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "record";
    ft[DESC] = "Number of currently enqueued records (durable messages) (High)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "recordDepthLow";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "record";
    ft[DESC] = "Number of currently enqueued records (durable messages) (Low)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "enqueues";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total enqueued records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "dequeues";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total dequeued records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "txn";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "record";
    ft[DESC] = "Total open transactions (xids) on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "txnEnqueues";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transactional enqueued records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "txnDequeues";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transactional dequeued records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "txnCommits";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transactional commit records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "txnAborts";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "record";
    ft[DESC] = "Total transactional abort records on journal";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "outstandingAIOs";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "aio_op";
    ft[DESC] = "Number of currently outstanding AIO requests in Async IO system";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "outstandingAIOsHigh";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "aio_op";
    ft[DESC] = "Number of currently outstanding AIO requests in Async IO system (High)";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "outstandingAIOsLow";
    ft[TYPE] = TYPE_U32;
    ft[UNIT] = "aio_op";
    ft[DESC] = "Number of currently outstanding AIO requests in Async IO system (Low)";
    buf.putMap(ft);


    // Methods

    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}


void Journal::aggregatePerThreadStats(struct PerThreadStats* totals) const
{
    totals->enqueues = 0;
    totals->dequeues = 0;
    totals->txn = 0;
    totals->txnEnqueues = 0;
    totals->txnDequeues = 0;
    totals->txnCommits = 0;
    totals->txnAborts = 0;

    for (int idx = 0; idx < maxThreads; idx++) {
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats != 0) {
            totals->enqueues += threadStats->enqueues;
            totals->dequeues += threadStats->dequeues;
            totals->txn += threadStats->txn;
            totals->txnEnqueues += threadStats->txnEnqueues;
            totals->txnDequeues += threadStats->txnDequeues;
            totals->txnCommits += threadStats->txnCommits;
            totals->txnAborts += threadStats->txnAborts;

        }
    }
}



uint32_t Journal::writePropertiesSize() const
{
    uint32_t size = writeTimestampsSize();

    size += 16;  // queueRef
    size += (1 + queueName.length());  // queueName
    size += (1 + directory.length());  // directory
    size += 4;  // writePageSize
    size += 4;  // writePages

    return size;
}

void Journal::readProperties (const std::string& _sBuf)
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


    {std::string _s; buf.getRawData(_s, queueRef.encodedSize()); queueRef.decode(_s);};
    buf.getShortString(queueName);
    buf.getShortString(directory);
    writePageSize = buf.getLong();
    writePages = buf.getLong();


    delete [] _tmpBuf;
}

void Journal::writeProperties (std::string& _sBuf) const
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



    {std::string _s; queueRef.encode(_s); buf.putRawData(_s);};
    buf.putShortString(queueName);
    buf.putShortString(directory);
    buf.putLong(writePageSize);
    buf.putLong(writePages);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Journal::writeStatistics (std::string& _sBuf, bool skipHeaders)
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

    buf.putLong(recordDepth);
    buf.putLong(recordDepthHigh);
    buf.putLong(recordDepthLow);
    buf.putLongLong(totals.enqueues);
    buf.putLongLong(totals.dequeues);
    buf.putLong(totals.txn);
    buf.putLongLong(totals.txnEnqueues);
    buf.putLongLong(totals.txnDequeues);
    buf.putLongLong(totals.txnCommits);
    buf.putLongLong(totals.txnAborts);
    buf.putLong(outstandingAIOs);
    buf.putLong(outstandingAIOsHigh);
    buf.putLong(outstandingAIOsLow);


    // Maintenance of hi-lo statistics
    recordDepthHigh = recordDepth;
    recordDepthLow  = recordDepth;
    outstandingAIOsHigh = outstandingAIOs;
    outstandingAIOsLow  = outstandingAIOs;



    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Journal::doMethod (string&, const string&, string& outStr, const string&)
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

std::string Journal::getKey() const
{
    std::stringstream key;

    key << queueName;
    return key.str();
}


void Journal::mapEncodeValues (::qpid::types::Variant::Map& _map,
                                              bool includeProperties,
                                              bool includeStatistics)
{
    using namespace ::qpid::types;
    Mutex::ScopedLock mutex(accessLock);

    if (includeProperties) {
        configChanged = false;
    _map["queueRef"] = ::qpid::types::Variant(queueRef);
    _map["queueName"] = ::qpid::types::Variant(queueName);
    _map["directory"] = ::qpid::types::Variant(directory);
    _map["writePageSize"] = ::qpid::types::Variant(writePageSize);
    _map["writePages"] = ::qpid::types::Variant(writePages);

    }

    if (includeStatistics) {
        instChanged = false;


        struct PerThreadStats totals;
        aggregatePerThreadStats(&totals);



    _map["recordDepth"] = ::qpid::types::Variant(recordDepth);
    _map["recordDepthHigh"] = ::qpid::types::Variant(recordDepthHigh);
    _map["recordDepthLow"] = ::qpid::types::Variant(recordDepthLow);
    _map["enqueues"] = ::qpid::types::Variant(totals.enqueues);
    _map["dequeues"] = ::qpid::types::Variant(totals.dequeues);
    _map["txn"] = ::qpid::types::Variant(totals.txn);
    _map["txnEnqueues"] = ::qpid::types::Variant(totals.txnEnqueues);
    _map["txnDequeues"] = ::qpid::types::Variant(totals.txnDequeues);
    _map["txnCommits"] = ::qpid::types::Variant(totals.txnCommits);
    _map["txnAborts"] = ::qpid::types::Variant(totals.txnAborts);
    _map["outstandingAIOs"] = ::qpid::types::Variant(outstandingAIOs);
    _map["outstandingAIOsHigh"] = ::qpid::types::Variant(outstandingAIOsHigh);
    _map["outstandingAIOsLow"] = ::qpid::types::Variant(outstandingAIOsLow);


    // Maintenance of hi-lo statistics
    recordDepthHigh = recordDepth;
    recordDepthLow  = recordDepth;
    outstandingAIOsHigh = outstandingAIOs;
    outstandingAIOsLow  = outstandingAIOs;


    }
}

void Journal::mapDecodeValues (const ::qpid::types::Variant::Map& _map)
{
    ::qpid::types::Variant::Map::const_iterator _i;
    Mutex::ScopedLock mutex(accessLock);

    if ((_i = _map.find("queueRef")) != _map.end()) {
        queueRef = _i->second;
    } else {
        queueRef = ::qpid::management::ObjectId();
    }
    if ((_i = _map.find("queueName")) != _map.end()) {
        queueName = (_i->second).getString();
    } else {
        queueName = "";
    }
    if ((_i = _map.find("directory")) != _map.end()) {
        directory = (_i->second).getString();
    } else {
        directory = "";
    }
    if ((_i = _map.find("writePageSize")) != _map.end()) {
        writePageSize = _i->second;
    } else {
        writePageSize = 0;
    }
    if ((_i = _map.find("writePages")) != _map.end()) {
        writePages = _i->second;
    } else {
        writePages = 0;
    }

}

void Journal::doMethod (string&, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string&)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;


    outMap["_status_code"] = (uint32_t) status;
    outMap["_status_text"] = Manageable::StatusText(status, text);
}
