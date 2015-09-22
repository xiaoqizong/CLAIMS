/*
 * Logging.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: wangli
 */
#include "./Logging.h"

#include <string.h>
#include <iostream>
#include "log/logging.h"

#define   likely(x)     __builtin_expect(!!(x), 1)
#define   unlikely(x)   __builtin_expect(!!(x), 0)

// #define CLAIMS_QUEIT
// #ifndef CLAIMS_QUEIT  // If defined, all the output information is binded.
#define DEBUG_QUERY_OPTIMIZATION
#define DEBUG_STORAGE_MANAGER
#define DEBUG_CONFIG
#define DEBUG_EXPANDER_TRACKER
#define DEBUG_BLOCK_STREAM_EXPANDER
#define DEBUG_BLOCK_STREAM_JOIN
#define DEBUG_PERFORMANCE_TOP
#define DEBUG_COORDINATOR
#define DEBUG_ENVIRONMENT
#define DEBUG_ADAPTIVE_END_POINT
#define DEBUG_EXCHANGE_ITERATOR_LOWER_WITH_WIDE_DEPENDENCY
#define DEBUG_EXCHANGE_ITERATOR_WITH_WIDE_DENPENDENCY
#define DEBUG_EXCHANGE_ITERATOR_EAGER
#define DEBUG_EXCHANGE_ITERATOR_EAGER_LOWER

#define DEBUG_EXCHANGE_REGISTER
#define DEBUG_EXCHANGE_TRACKER

#define DEBUG_PORT_MANAGER
#define DEBUG_ITERATOR_EXECUTOR_SLAVE
#define DEBUG_ITERATOR_EXECUTOR_MASTER

#define DEBUG_CLIENT
#define DEBUG_CLIENT_LISTENER

#define DEBUG_EXCHANGE_ITERATOR_EAGER
#define DEBUG_EXCHANGE_ITERATOR_SENDER_MATERIALIZED
#define DEBUG_EXPANDABLE_BLOCK_STREAM_EXCHANGE_MATERIALIZED
#define DEBUG_BLOCK_STREAM_EXCHANGE_LOWER_BASE
#define DEBUG_EXPANDABLE_BLOCK_STREAM_EXCHANGE_LM

#define DEBUG_RESOURCE_MANAGER_MASTER
#define DEBUG_RESOURCE_MANAGER_SLAVE
#define DEBUG_CATALOG
#define DEBUG_BUFFER_MANAGER

#define DEBUG_AST_PARSER

#define DEBUG_THREAD_POOL
#define SQL_PARSER

// #endif  //CLAIMS_QUEIT


void RawLog(const char* where, const char* format, va_list args) {
  const int kMessageMaxLength = 1000;  // set initial message length
  char p[kMessageMaxLength];
  memset(p, 0, kMessageMaxLength*sizeof(char));

  int real_length = vsnprintf(p, kMessageMaxLength, format, args);

  if (unlikely(real_length < 0)) {  // check error code and output
    LOG(ERROR) << "vsnprintf error. " << strerror(errno) << std::endl;
  } else if (likely(real_length < kMessageMaxLength)) {
    // if it worked, output the message
//    std::cout<<where<<p<<std::endl;
    LOG(INFO) << where << p << std::endl;
  } else {  // try again with more space
    int new_message_length = real_length + 1;
    char* temp = new char[new_message_length];
    if (temp == NULL) {
      LOG(ERROR) << "new " << new_message_length << " bytes failed."
          << strerror(errno) << std::endl;
      return;
    }
    // if enough space got, do it again
    real_length = vsnprintf(temp, new_message_length, format, args);
    LOG(INFO) << where << temp << std::endl;
    delete[] temp;
  }
}


void RawElog(const char* where, const char* format, va_list args) {
  const int message_max_length = 1000;  // set initial message length
  char p[message_max_length];

  int real_length = vsnprintf(p, message_max_length, format, args);

  if (unlikely(real_length < 0)) {  // check error code and output
    LOG(ERROR) << "vsnprintf error. " << strerror(errno) << std::endl;
  } else if (likely(real_length < message_max_length)) {
    // if it worked, output the message
    LOG(ERROR) << where << p << std::endl;
  } else {  // try again with more space
    int new_message_length = real_length + 1;
    char* temp = new char[new_message_length];
    if (temp == NULL) {
      LOG(ERROR) << "new " << new_message_length << " bytes failed."
          << strerror(errno) << std::endl;
      return;
    }
    // if enough space got, do it again
    real_length = vsnprintf(temp, new_message_length, format, args);
    LOG(ERROR) << where << temp << std::endl;
    delete[] temp;
  }
}

void IteratorExecutorMasterLogging::log(const char* format, ...) {
#ifdef DEBUG_ITERATOR_EXECUTOR_MASTER
  va_list arg;
  va_start(arg, format);
  RawLog("[IteratorExecutorMaster]: ", format, arg);
  va_end(arg);
#endif
}
void IteratorExecutorMasterLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[IteratorExecutorMaster]: ", format, arg);
  va_end(arg);
}

void IteratorExecutorSlaveLogging::log(const char* format, ...) {
#ifdef DEBUG_ITERATOR_EXECUTOR_SLAVE
  va_list arg;
  va_start(arg, format);
  RawLog("[IteratorExecutorSlave]: ", format, arg);
  va_end(arg);
#endif
}
void IteratorExecutorSlaveLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[IteratorExecutorSlave]: ", format, arg);
  va_end(arg);
}

void EnvironmentLogging::log(const char* format, ...) {
#ifdef DEBUG_ENVIRONMENT
  va_list arg;
  va_start(arg, format);
  RawLog("[Environment]: ", format, arg);
  va_end(arg);
#endif
}
void EnvironmentLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[Environment]: ", format, arg);
  va_end(arg);
}

void AdaptiveEndPointLogging::log(const char* format, ...) {
#ifdef DEBUG_ADAPTIVE_END_POINT
  va_list arg;
  va_start(arg, format);
  RawLog("[AdaptiveEndPoint]: ", format, arg);
  va_end(arg);
#endif
}
void AdaptiveEndPointLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[AdaptiveEndPoint]: ", format, arg);
  va_end(arg);
}

void CoordinatorLogging::log(const char* format, ...) {
#ifdef DEBUG_COORDINATOR
  va_list arg;
  va_start(arg, format);
  RawLog("[Coordinator]: ", format, arg);
  va_end(arg);
#endif
}
void CoordinatorLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[Coordinator]: ", format, arg);
  va_end(arg);
}

void ExchangeTrackerLogging::log(const char* format, ...) {
#ifdef DEBUG_EXCHANGE_TRACKER
  va_list arg;
  va_start(arg, format);
  RawLog("[ExchangeTracker]: ", format, arg);
  va_end(arg);
#endif
}
void ExchangeTrackerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ExchangeTracker]: ", format, arg);
  va_end(arg);
}

void ExpanderTrackerLogging::log(const char* format, ...) {
#ifdef DEBUG_EXPANDER_TRACKER
  va_list arg;
  va_start(arg, format);
  RawLog("[ExpanderTracker]: ", format, arg);
  va_end(arg);
#endif
}
void ExpanderTrackerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ExpanderTracker]: ", format, arg);
  va_end(arg);
}

void ExchangeIteratorEagerLogging::log(const char* format, ...) {
#ifdef DEBUG_EXCHANGE_ITERATOR_EAGER
  va_list arg;
  va_start(arg, format);
  RawLog("[ExchangeEagerUpper]: ", format, arg);
  va_end(arg);
#endif
}
void ExchangeIteratorEagerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ExchangeEagerUpper]: ", format, arg);
  va_end(arg);
}

void ExchangeIteratorEagerLowerLogging::log(const char* format, ...) {
#ifdef DEBUG_EXCHANGE_ITERATOR_EAGER
  va_list arg;
  va_start(arg, format);
  RawLog("[ExchangeEagerLower]: ", format, arg);
  va_end(arg);
#endif
}
void ExchangeIteratorEagerLowerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ExchangeEagerLower]: ", format, arg);
  va_end(arg);
}

void ExchangeIteratorSenderMaterialized::log(const char* format, ...) {
#ifdef DEBUG_EXCHANGE_ITERATOR_SENDER_MATERIALIZED
  va_list arg;
  va_start(arg, format);
  RawLog("[ExchangeEagerLowerMaterialized]: ", format, arg);
  va_end(arg);
#endif
}
void ExchangeIteratorSenderMaterialized::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ExchangeEagerLowerMaterialized]: ", format, arg);
  va_end(arg);
}

void CatalogLogging::log(const char* format, ...) {
#ifdef DEBUG_CATALOG
  va_list arg;
  va_start(arg, format);
  RawLog("[Catalog]: ", format, arg);
  va_end(arg);
#endif
}
void CatalogLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[Catalog]: ", format, arg);
  va_end(arg);
}

void ResourceManagerMasterLogging::log(const char* format, ...) {
#ifdef DEBUG_RESOURCE_MANAGER_MASTER
  va_list arg;
  va_start(arg, format);
  RawLog("[ResourceManagerMaster]: ", format, arg);
  va_end(arg);
#endif
}
void ResourceManagerMasterLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ResourceManagerMaster]: ", format, arg);
  va_end(arg);
}

void ResourceManagerSlaveLogging::log(const char* format, ...) {
#ifdef DEBUG_RESOURCE_MANAGER_SLAVE
  va_list arg;
  va_start(arg, format);
  RawLog("[ResourceManagerSlave]: ", format, arg);
  va_end(arg);
#endif
}
void ResourceManagerSlaveLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ResourceManagerSlave]: ", format, arg);
  va_end(arg);
}

void StorageManagerLogging::log(const char* format, ...) {
#ifdef DEBUG_STORAGE_MANAGER
  va_list arg;
  va_start(arg, format);
  RawLog("[StorageManager]: ", format, arg);
  va_end(arg);
#endif
}
void StorageManagerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[StorageManager]: ", format, arg);
  va_end(arg);
}
void StorageManagerMasterLogging::log(const char* format, ...) {
#ifdef DEBUG_STORAGE_MANAGER
  va_list arg;
  va_start(arg, format);
  RawLog("[StorageManagerMaster]: ", format, arg);
  va_end(arg);
#endif
}
void StorageManagerMasterLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[StorageManagerMaster]: ", format, arg);
  va_end(arg);
}

void BufferManagerLogging::log(const char* format, ...) {
#ifdef DEBUG_BUFFER_MANAGER
  va_list arg;
  va_start(arg, format);
  RawLog("[BufferManager]: ", format, arg);
  va_end(arg);
#endif
}
void BufferManagerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[BufferManager]: ", format, arg);
  va_end(arg);
}

void ASTParserLogging::log(const char* format, ...) {
#ifdef DEBUG_AST_PARSER
  va_list arg;
  va_start(arg, format);
  RawLog("[ASTParser]: ", format, arg);
  va_end(arg);
#endif
}
void ASTParserLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ASTParser]: ", format, arg);
  va_end(arg);
}

void ClientListenerLogging::log(const char* format, ...) {
#ifdef DEBUG_CLIENT_LISTENER
  va_list arg;
  va_start(arg, format);
  RawLog("[ClientListener]: ", format, arg);
  va_end(arg);
#endif
}
void ClientListenerLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ClientListener]: ", format, arg);
  va_end(arg);
}

void BlockStreamExpanderLogging::log(const char* format, ...) {
#ifdef DEBUG_BLOCK_STREAM_EXPANDER
  va_list arg;
  va_start(arg, format);
  RawLog("[BlockStreamExpander]: ", format, arg);
  va_end(arg);
#endif
}
void BlockStreamExpanderLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[BlockStreamExpander]: ", format, arg);
  va_end(arg);
}
void PerformanceTopLogging::log(const char* format, ...) {
#ifdef DEBUG_PERFORMANCE_TOP
  va_list arg;
  va_start(arg, format);
  RawLog("[PerformanceTop]: ", format, arg);
  va_end(arg);
#endif
}
void PerformanceTopLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[PerformanceTop]: ", format, arg);
  va_end(arg);
}
void QueryOptimizationLogging::log(const char* format, ...) {
#ifdef DEBUG_QUERY_OPTIMIZATION
  va_list arg;
  va_start(arg, format);
  RawLog("[QueryOptimization]: ", format, arg);
  va_end(arg);
#endif
}
void QueryOptimizationLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[QueryOptimization]: ", format, arg);
  va_end(arg);
}

void BlockStreamJoinLogging::log(const char* format, ...) {
#ifdef DEBUG_BLOCK_STREAM_JOIN
  va_list arg;
  va_start(arg, format);
  RawLog("[BlockStreamJoin]: ", format, arg);
  va_end(arg);
#endif
}

void BlockStreamJoinLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[BlockStreamJoin]:", format, arg);
  va_end(arg);
}

void SQLParse_log(const char* format, ...) {
#ifdef SQL_PARSER
  va_list arg;
  va_start(arg, format);
  RawLog("[SQLParse]:", format, arg);
  va_end(arg);
#endif
}

void SQLParse_elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawLog("[SQLParse]: ", format, arg);
  va_end(arg);
}

void ClientLogging::log(const char* format, ...) {
#ifdef DEBUG_CLIENT
  va_list arg;
  va_start(arg, format);
  RawLog("[Client]: ", format, arg);
  va_end(arg);
#endif
}

void ClientLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[Client]: ", format, arg);
  va_end(arg);
}

void ThreadPoolLogging::log(const char* format, ...) {
#ifdef DEBUG_THREAD_POOL
  va_list arg;
  va_start(arg, format);
  RawLog("[ThreadPool]: ", format, arg);
  va_end(arg);
#endif
}

void ThreadPoolLogging::elog(const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  RawElog("[ThreadPool]: ", format, arg);
  va_end(arg);
}
