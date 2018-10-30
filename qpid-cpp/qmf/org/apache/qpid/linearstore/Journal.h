
#ifndef _MANAGEMENT_ORG_APACHE_QPID_LINEARSTORE_JOURNAL_
#define _MANAGEMENT_ORG_APACHE_QPID_LINEARSTORE_JOURNAL_

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

#include "qpid/management/ManagementObject.h"

#include "qmf/BrokerImportExport.h"
#include <boost/shared_ptr.hpp>

#include <limits>

namespace qpid {
    namespace management {
        class ManagementAgent;
    }
}

namespace qmf {
namespace org {
namespace apache {
namespace qpid {
namespace linearstore {


QPID_BROKER_CLASS_EXTERN class Journal : public ::qpid::management::ManagementObject
{
  private:

    static std::string packageName;
    static std::string className;
    static uint8_t     md5Sum[MD5_LEN];


    // Properties
    ::qpid::management::ObjectId queueRef;
    std::string queueName;
    std::string directory;
    uint32_t writePageSize;
    uint32_t writePages;

    // Statistics
    uint32_t  recordDepth;
    uint32_t  recordDepthHigh;
    uint32_t  recordDepthLow;
    uint32_t  outstandingAIOs;
    uint32_t  outstandingAIOsHigh;
    uint32_t  outstandingAIOsLow;


    // Per-Thread Statistics

 public:    
    struct PerThreadStats {
        uint64_t  enqueues;
        uint64_t  dequeues;
        uint32_t  txn;
        uint64_t  txnEnqueues;
        uint64_t  txnDequeues;
        uint64_t  txnCommits;
        uint64_t  txnAborts;

    };
 private:

    struct PerThreadStats** perThreadStatsArray;

    inline struct PerThreadStats* getThreadStats() {
        int idx = getThreadIndex();
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats == 0) {
            threadStats = new(PerThreadStats);
            perThreadStatsArray[idx] = threadStats;
            threadStats->enqueues = 0;
            threadStats->dequeues = 0;
            threadStats->txn = 0;
            threadStats->txnEnqueues = 0;
            threadStats->txnDequeues = 0;
            threadStats->txnCommits = 0;
            threadStats->txnAborts = 0;

        }
        return threadStats;
    }

    void aggregatePerThreadStats(struct PerThreadStats*) const;

  public:

    typedef boost::shared_ptr<Journal> shared_ptr;


    QPID_BROKER_EXTERN static void writeSchema(std::string& schema);
    QPID_BROKER_EXTERN void mapEncodeValues(::qpid::types::Variant::Map& map,
                                          bool includeProperties=true,
                                          bool includeStatistics=true);
    QPID_BROKER_EXTERN void mapDecodeValues(const ::qpid::types::Variant::Map& map);
    QPID_BROKER_EXTERN void doMethod(std::string&           methodName,
                                   const ::qpid::types::Variant::Map& inMap,
                                   ::qpid::types::Variant::Map& outMap,
                                   const std::string& userId);
    QPID_BROKER_EXTERN std::string getKey() const;

    QPID_BROKER_EXTERN uint32_t writePropertiesSize() const;
    QPID_BROKER_EXTERN void readProperties(const std::string& buf);
    QPID_BROKER_EXTERN void writeProperties(std::string& buf) const;
    QPID_BROKER_EXTERN void writeStatistics(std::string& buf, bool skipHeaders = false);
    QPID_BROKER_EXTERN void doMethod(std::string& methodName,
                                   const std::string& inBuf,
                                   std::string& outBuf,
                                   const std::string& userId);


    writeSchemaCall_t getWriteSchemaCall() { return writeSchema; }


    QPID_BROKER_EXTERN Journal(
        ::qpid::management::ManagementAgent* agent,
        ::qpid::management::Manageable* coreObject, const std::string& _queueName);

    QPID_BROKER_EXTERN ~Journal();

    void debugStats (const std::string& comment);

    void setReference(::qpid::management::ObjectId objectId) { queueRef = objectId; }


    QPID_BROKER_EXTERN static void registerSelf(
        ::qpid::management::ManagementAgent* agent);

    std::string& getPackageName() const { return packageName; }
    std::string& getClassName() const { return className; }
    uint8_t* getMd5Sum() const { return md5Sum; }

    // Method IDs

    // Accessor Methods
    inline void set_queueRef (const ::qpid::management::ObjectId& val) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        queueRef = val;
        configChanged = true;
    }
    inline const ::qpid::management::ObjectId& get_queueRef() {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        return queueRef;
    }
    inline void set_directory (const std::string& val) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        directory = val;
        configChanged = true;
    }
    inline const std::string& get_directory() {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        return directory;
    }
    inline void set_writePageSize (uint32_t val) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        writePageSize = val;
        configChanged = true;
    }
    inline uint32_t get_writePageSize() {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        return writePageSize;
    }
    inline void set_writePages (uint32_t val) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        writePages = val;
        configChanged = true;
    }
    inline uint32_t get_writePages() {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        return writePages;
    }
    inline void inc_recordDepth (uint32_t by = 1) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        recordDepth += by;
        if (recordDepthHigh < recordDepth)
            recordDepthHigh = recordDepth;
        instChanged = true;
    }
    inline void dec_recordDepth (uint32_t by = 1) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        recordDepth -= by;
        if (recordDepthLow > recordDepth)
            recordDepthLow = recordDepth;
        instChanged = true;
    }
    inline void inc_enqueues (uint64_t by = 1) {
        getThreadStats()->enqueues += by;
        instChanged = true;
    }
    inline void dec_enqueues (uint64_t by = 1) {
        getThreadStats()->enqueues -= by;
        instChanged = true;
    }
    inline void inc_dequeues (uint64_t by = 1) {
        getThreadStats()->dequeues += by;
        instChanged = true;
    }
    inline void dec_dequeues (uint64_t by = 1) {
        getThreadStats()->dequeues -= by;
        instChanged = true;
    }
    inline void inc_txn (uint32_t by = 1) {
        getThreadStats()->txn += by;
        instChanged = true;
    }
    inline void dec_txn (uint32_t by = 1) {
        getThreadStats()->txn -= by;
        instChanged = true;
    }
    inline void inc_txnEnqueues (uint64_t by = 1) {
        getThreadStats()->txnEnqueues += by;
        instChanged = true;
    }
    inline void dec_txnEnqueues (uint64_t by = 1) {
        getThreadStats()->txnEnqueues -= by;
        instChanged = true;
    }
    inline void inc_txnDequeues (uint64_t by = 1) {
        getThreadStats()->txnDequeues += by;
        instChanged = true;
    }
    inline void dec_txnDequeues (uint64_t by = 1) {
        getThreadStats()->txnDequeues -= by;
        instChanged = true;
    }
    inline void inc_txnCommits (uint64_t by = 1) {
        getThreadStats()->txnCommits += by;
        instChanged = true;
    }
    inline void dec_txnCommits (uint64_t by = 1) {
        getThreadStats()->txnCommits -= by;
        instChanged = true;
    }
    inline void inc_txnAborts (uint64_t by = 1) {
        getThreadStats()->txnAborts += by;
        instChanged = true;
    }
    inline void dec_txnAborts (uint64_t by = 1) {
        getThreadStats()->txnAborts -= by;
        instChanged = true;
    }
    inline void inc_outstandingAIOs (uint32_t by = 1) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        outstandingAIOs += by;
        if (outstandingAIOsHigh < outstandingAIOs)
            outstandingAIOsHigh = outstandingAIOs;
        instChanged = true;
    }
    inline void dec_outstandingAIOs (uint32_t by = 1) {
        ::qpid::management::Mutex::ScopedLock mutex(accessLock);
        outstandingAIOs -= by;
        if (outstandingAIOsLow > outstandingAIOs)
            outstandingAIOsLow = outstandingAIOs;
        instChanged = true;
    }



    struct PerThreadStats* getStatistics() { return getThreadStats(); }
    void statisticsUpdated() { instChanged = true; }

};

}}}}}

#endif  /*!_MANAGEMENT_JOURNAL_*/
