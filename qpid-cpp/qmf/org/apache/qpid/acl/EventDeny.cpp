
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
#include "EventDeny.h"

using namespace qmf::org::apache::qpid::acl;
using           qpid::management::ManagementAgent;
using           qpid::management::Manageable;
using           qpid::management::ManagementObject;
using           qpid::management::Args;
using           qpid::management::Mutex;
using           std::string;

string  EventDeny::packageName  = string ("org.apache.qpid.acl");
string  EventDeny::eventName    = string ("deny");
uint8_t EventDeny::md5Sum[16]   =
    {0x8c,0x6a,0xec,0x3d,0xcb,0x5a,0xe0,0xbf,0x83,0xdc,0xba,0xcc,0x10,0x45,0xb,0x3a};

EventDeny::EventDeny (const std::string& _userId,
        const std::string& _action,
        const std::string& _objectType,
        const std::string& _objectName,
        const ::qpid::types::Variant::Map& _arguments) :
    userId(_userId),
    action(_action),
    objectType(_objectType),
    objectName(_objectName),
    arguments(_arguments)
{}

namespace {
    const string NAME("name");
    const string TYPE("type");
    const string DESC("desc");
    const string ARGCOUNT("argCount");
    const string ARGS("args");
}

void EventDeny::registerSelf(ManagementAgent* agent)
{
    agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
}

void EventDeny::writeSchema (std::string& schema)
{
    const int _bufSize = 65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer buf(_msgChars, _bufSize);
    ::qpid::types::Variant::Map ft;

    // Schema class header:
    buf.putOctet       (CLASS_KIND_EVENT);
    buf.putShortString (packageName); // Package Name
    buf.putShortString (eventName);   // Event Name
    buf.putBin128      (md5Sum);      // Schema Hash
    buf.putShort       (5); // Argument Count

    // Arguments
    ft.clear();
    ft[NAME] = "userId";
    ft[TYPE] = TYPE_SSTR;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "action";
    ft[TYPE] = TYPE_SSTR;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "objectType";
    ft[TYPE] = TYPE_SSTR;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "objectName";
    ft[TYPE] = TYPE_SSTR;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "arguments";
    ft[TYPE] = TYPE_FTABLE;
    buf.putMap(ft);


    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}

void EventDeny::encode(std::string& _sBuf) const
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qpid::management::Buffer buf(_msgChars, _bufSize);

    buf.putShortString(userId);
    buf.putShortString(action);
    buf.putShortString(objectType);
    buf.putShortString(objectName);
    buf.putMap(arguments);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void EventDeny::mapEncode(::qpid::types::Variant::Map& map) const
{
    using namespace ::qpid::types;
    map["userId"] = ::qpid::types::Variant(userId);
    map["action"] = ::qpid::types::Variant(action);
    map["objectType"] = ::qpid::types::Variant(objectType);
    map["objectName"] = ::qpid::types::Variant(objectName);
    map["arguments"] = ::qpid::types::Variant(arguments);

}

bool EventDeny::match(const std::string& evt, const std::string& pkg)
{
    return eventName == evt && packageName == pkg;
}
