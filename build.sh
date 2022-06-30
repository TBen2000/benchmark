#!/usr/bin/bash

CC="g++"
CFLAGS="-g"
LDFLAGS="-lsqlite3 -lprotobuf -lpthread"
PROTOBUF_FILES="Encoder/ProtobufEncoder.cpp Encoder/Protobuf/addressbook.pb.cc"

CXXFILES="main.cpp Measure.cpp Encoder/TextEncoder.cpp $PROTOBUF_FILES ConcreteDataStructure/Person.cpp  DataStorages/FileDataStorage.cpp DataStorages/PrintDataStorage.cpp DataStorages/VoidDataStorage.cpp DataStorages/SQLiteTEXTDataStorage.cpp DataStorages/SQLiteBLOBDataStorage.cpp Scenarios/PersonScenario.cpp"
OUTPUT="main"

echo "building ..."
${CC} $CXXFILES $CFLAGS $LDFLAGS -o $OUTPUT
echo "done"