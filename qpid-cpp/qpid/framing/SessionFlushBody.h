#ifndef QPID_FRAMING_SESSIONFLUSHBODY_H
#define QPID_FRAMING_SESSIONFLUSHBODY_H
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

class QPID_COMMON_CLASS_EXTERN SessionFlushBody : public AMQMethodBody {
    uint16_t flags;
public:
    static const ClassId CLASS_ID = 0x2;
    static const MethodId METHOD_ID = 0xc;
    SessionFlushBody(
        ProtocolVersion, bool _expected,
        bool _confirmed,
        bool _completed) : 
        flags(0){
        setExpected(_expected);
        setConfirmed(_confirmed);
        setCompleted(_completed);
    }
    SessionFlushBody(ProtocolVersion=ProtocolVersion())  : flags(0) {}
    
    QPID_COMMON_EXTERN void setExpected(bool _expected);
    QPID_COMMON_EXTERN bool getExpected() const;
    QPID_COMMON_EXTERN void setConfirmed(bool _confirmed);
    QPID_COMMON_EXTERN bool getConfirmed() const;
    QPID_COMMON_EXTERN void setCompleted(bool _completed);
    QPID_COMMON_EXTERN bool getCompleted() const;
virtual uint8_t type() const { return 0;/*control segment*/ }
    typedef void ResultType;

    template <class T> ResultType invoke(T& invocable) const {
        return invocable.flush(getExpected(), getConfirmed(), getCompleted());
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
}; /* class SessionFlushBody */

}}
#endif  /*!QPID_FRAMING_SESSIONFLUSHBODY_H*/
