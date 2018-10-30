#ifndef QPID_FRAMING_CONNECTIONREDIRECTBODY_H
#define QPID_FRAMING_CONNECTIONREDIRECTBODY_H
/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

///
/// This file was automatically generated from the AMQP specification.
/// Do not edit.
///


#include "qpid/framing/AMQMethodBody.h"
#include "qpid/framing/AMQP_ServerOperations.h"
#include "qpid/framing/MethodBodyConstVisitor.h"

#include <ostream>
#include "qpid/framing/amqp_types_full.h"
#include "qpid/framing/reply_exceptions.h"
#include "qpid/CommonImportExport.h"

namespace qpid {
namespace framing {

class QPID_COMMON_CLASS_EXTERN ConnectionRedirectBody : public AMQMethodBody {
    std::string host;
    Array knownHosts;
    uint16_t flags;
public:
    static const ClassId CLASS_ID = 0x1;
    static const MethodId METHOD_ID = 0x9;
    ConnectionRedirectBody(
        ProtocolVersion, const std::string& _host,
        const Array& _knownHosts) : 
        host(_host),
        knownHosts(_knownHosts),
        flags(0){
        flags |= (1 << 8);
        flags |= (1 << 9);
        if (host.size() >= 65536) throw IllegalArgumentException("Value for host is too large");
    }
    ConnectionRedirectBody(ProtocolVersion=ProtocolVersion())  : flags(0) {}
    
    QPID_COMMON_EXTERN void setHost(const std::string& _host);
    QPID_COMMON_EXTERN const std::string& getHost() const;
    QPID_COMMON_EXTERN bool hasHost() const;
    QPID_COMMON_EXTERN void clearHostFlag();
    QPID_COMMON_EXTERN void setKnownHosts(const Array& _knownHosts);
    QPID_COMMON_EXTERN const Array& getKnownHosts() const;
    QPID_COMMON_EXTERN bool hasKnownHosts() const;
    QPID_COMMON_EXTERN void clearKnownHostsFlag();
virtual uint8_t type() const { return 0;/*control segment*/ }
    typedef void ResultType;

    template <class T> ResultType invoke(T& invocable) const {
        return invocable.redirect(getHost(), getKnownHosts());
    }

    using  AMQMethodBody::accept;
    void accept(MethodBodyConstVisitor& v) const { v.visit(*this); }
    boost::intrusive_ptr<AMQBody> clone() const { return BodyFactory::copy(*this); }

    ClassId amqpClassId() const { return CLASS_ID; }
    MethodId amqpMethodId() const { return METHOD_ID; }
    bool isContentBearing() const { return  false; }
    bool resultExpected() const { return  false; }
    bool responseExpected() const { return  false; }
    QPID_COMMON_EXTERN void encode(Buffer&) const;
    QPID_COMMON_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_COMMON_EXTERN void encodeStructBody(Buffer&) const;
    QPID_COMMON_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_COMMON_EXTERN uint32_t encodedSize() const;
    QPID_COMMON_EXTERN uint32_t bodySize() const;
    QPID_COMMON_EXTERN void print(std::ostream& out) const;
}; /* class ConnectionRedirectBody */

}}
#endif  /*!QPID_FRAMING_CONNECTIONREDIRECTBODY_H*/
