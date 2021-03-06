#ifndef QPID_FRAMING_CONSTANTS_H
#define QPID_FRAMING_CONSTANTS_H
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



namespace qpid {
namespace framing {

enum AmqpConstant {
    MIN_MAX_FRAME_SIZE=4096,
    CONNECTION_CLASS_ID=0x1,
    CONNECTION_START_METHOD_ID=0x1,
    CONNECTION_START_OK_METHOD_ID=0x2,
    CONNECTION_SECURE_METHOD_ID=0x3,
    CONNECTION_SECURE_OK_METHOD_ID=0x4,
    CONNECTION_TUNE_METHOD_ID=0x5,
    CONNECTION_TUNE_OK_METHOD_ID=0x6,
    CONNECTION_OPEN_METHOD_ID=0x7,
    CONNECTION_OPEN_OK_METHOD_ID=0x8,
    CONNECTION_REDIRECT_METHOD_ID=0x9,
    CONNECTION_HEARTBEAT_METHOD_ID=0xa,
    CONNECTION_CLOSE_METHOD_ID=0xb,
    CONNECTION_CLOSE_OK_METHOD_ID=0xc,
    SESSION_CLASS_ID=0x2,
    SESSION_ATTACH_METHOD_ID=0x1,
    SESSION_ATTACHED_METHOD_ID=0x2,
    SESSION_DETACH_METHOD_ID=0x3,
    SESSION_DETACHED_METHOD_ID=0x4,
    SESSION_REQUEST_TIMEOUT_METHOD_ID=0x5,
    SESSION_TIMEOUT_METHOD_ID=0x6,
    SESSION_COMMAND_POINT_METHOD_ID=0x7,
    SESSION_EXPECTED_METHOD_ID=0x8,
    SESSION_CONFIRMED_METHOD_ID=0x9,
    SESSION_COMPLETED_METHOD_ID=0xa,
    SESSION_KNOWN_COMPLETED_METHOD_ID=0xb,
    SESSION_FLUSH_METHOD_ID=0xc,
    SESSION_GAP_METHOD_ID=0xd,
    EXECUTION_CLASS_ID=0x3,
    EXECUTION_SYNC_METHOD_ID=0x1,
    EXECUTION_RESULT_METHOD_ID=0x2,
    EXECUTION_EXCEPTION_METHOD_ID=0x3,
    MESSAGE_CLASS_ID=0x4,
    MESSAGE_TRANSFER_METHOD_ID=0x1,
    MESSAGE_ACCEPT_METHOD_ID=0x2,
    MESSAGE_REJECT_METHOD_ID=0x3,
    MESSAGE_RELEASE_METHOD_ID=0x4,
    MESSAGE_ACQUIRE_METHOD_ID=0x5,
    MESSAGE_RESUME_METHOD_ID=0x6,
    MESSAGE_SUBSCRIBE_METHOD_ID=0x7,
    MESSAGE_CANCEL_METHOD_ID=0x8,
    MESSAGE_SET_FLOW_MODE_METHOD_ID=0x9,
    MESSAGE_FLOW_METHOD_ID=0xa,
    MESSAGE_FLUSH_METHOD_ID=0xb,
    MESSAGE_STOP_METHOD_ID=0xc,
    TX_CLASS_ID=0x5,
    TX_SELECT_METHOD_ID=0x1,
    TX_COMMIT_METHOD_ID=0x2,
    TX_ROLLBACK_METHOD_ID=0x3,
    DTX_CLASS_ID=0x6,
    DTX_SELECT_METHOD_ID=0x1,
    DTX_START_METHOD_ID=0x2,
    DTX_END_METHOD_ID=0x3,
    DTX_COMMIT_METHOD_ID=0x4,
    DTX_FORGET_METHOD_ID=0x5,
    DTX_GET_TIMEOUT_METHOD_ID=0x6,
    DTX_PREPARE_METHOD_ID=0x7,
    DTX_RECOVER_METHOD_ID=0x8,
    DTX_ROLLBACK_METHOD_ID=0x9,
    DTX_SET_TIMEOUT_METHOD_ID=0xa,
    EXCHANGE_CLASS_ID=0x7,
    EXCHANGE_DECLARE_METHOD_ID=0x1,
    EXCHANGE_DELETE_METHOD_ID=0x2,
    EXCHANGE_QUERY_METHOD_ID=0x3,
    EXCHANGE_BIND_METHOD_ID=0x4,
    EXCHANGE_UNBIND_METHOD_ID=0x5,
    EXCHANGE_BOUND_METHOD_ID=0x6,
    QUEUE_CLASS_ID=0x8,
    QUEUE_DECLARE_METHOD_ID=0x1,
    QUEUE_DELETE_METHOD_ID=0x2,
    QUEUE_PURGE_METHOD_ID=0x3,
    QUEUE_QUERY_METHOD_ID=0x4,
    FILE_CLASS_ID=0x9,
    FILE_QOS_METHOD_ID=0x1,
    FILE_QOS_OK_METHOD_ID=0x2,
    FILE_CONSUME_METHOD_ID=0x3,
    FILE_CONSUME_OK_METHOD_ID=0x4,
    FILE_CANCEL_METHOD_ID=0x5,
    FILE_OPEN_METHOD_ID=0x6,
    FILE_OPEN_OK_METHOD_ID=0x7,
    FILE_STAGE_METHOD_ID=0x8,
    FILE_PUBLISH_METHOD_ID=0x9,
    FILE_RETURN_METHOD_ID=0xa,
    FILE_DELIVER_METHOD_ID=0xb,
    FILE_ACK_METHOD_ID=0xc,
    FILE_REJECT_METHOD_ID=0xd,
    STREAM_CLASS_ID=0xa,
    STREAM_QOS_METHOD_ID=0x1,
    STREAM_QOS_OK_METHOD_ID=0x2,
    STREAM_CONSUME_METHOD_ID=0x3,
    STREAM_CONSUME_OK_METHOD_ID=0x4,
    STREAM_CANCEL_METHOD_ID=0x5,
    STREAM_PUBLISH_METHOD_ID=0x6,
    STREAM_RETURN_METHOD_ID=0x7,
    STREAM_DELIVER_METHOD_ID=0x8
};

}} // namespace qpid::framing

#endif  /*!QPID_FRAMING_CONSTANTS_H*/
