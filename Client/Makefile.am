
AM_CPPFLAGS= -fPIC -fpermissive \
-I${BOOST_HOME} \
-I${BOOST_HOME}/boost/serialization \
-I${THERON_HOME}/Include 


AM_LDFLAGS=-lc -lm -lrt -lboost_serialization -lxs

if OPT_TCMALLOC
AM_CPPFLAGS+=-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
AM_LDFLAGS+=-ltcmalloc 
endif

LDADD = 	../Catalog/libcatalog.a \
		../Daemon/libdaemon.a \
		../common/Block/libblock.a \
		../common/Schema/libschema.a \
		${BOOST_HOME}/stage/lib/libboost_serialization.a \
		${BOOST_HOME}/stage/lib/libboost_serialization.so \
		${THERON_HOME}/Lib/libtherond.a		

noinst_LIBRARIES=libclient.a
libclient_a_SOURCES = \
	ClaimsServer.cpp			ClaimsServer.h \
	Client.cpp 				Client.h \
	ClientResponse.cpp 		ClientResponse.h \
	jsoncpp.cpp

SUBDIRS = Test json
DIST_SUBDIRS = Test json
