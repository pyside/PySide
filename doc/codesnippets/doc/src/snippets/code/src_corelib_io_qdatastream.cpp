void wrapInFunction()
{

//! [0]
file = QFile("file.dat")
file.open(QIODevice.WriteOnly)
# we will serialize the data into the file
out = QDataStream(file)
# serialize a string
out << "the answer is"    
# serialize an integer
out.writeInt32(42)
//! [0]


//! [1]
file = QFile("file.dat")
file.open(QIODevice.ReadOnly)
# read the data serialized from the file
i = QDataStream(file)
str = QString()
a = 0
# extract "the answer is" and 42
i >> str
a = i.readInt32()                  
//! [1]


//! [2]
stream.setVersion(QDataStream.Qt_4_0)
//! [2]


//! [3]
file = QFile("file.xxx")
file.open(QIODevice.WriteOnly)
out = QDataStream(file)

# Write a header with a "magic number" and a version
out.writeInt32(0xA0B0C0D0)
out.writeInt32(123)

out.setVersion(QDataStream.Qt_4_0);

// Write the data
out << lots_of_interesting_data
//! [3]


//! [4]
file = QFile("file.xxx")
file.open(QIODevice.ReadOnly)
i = QDataStream(file)

// Read and check the header
magic = i.readInt32()
if magic != 0xA0B0C0D0:
    return XXX_BAD_FILE_FORMAT

// Read the version
version = i.readInt32()
if version < 100:
    return XXX_BAD_FILE_TOO_OLD
if version > 123:
    return XXX_BAD_FILE_TOO_NEW

if version <= 110:
    in.setVersion(QDataStream.Qt_3_2)
else:
    in.setVersion(QDataStream.Qt_4_0)

// Read the data
in >> lots_of_interesting_data
if version >= 120:
    in >> data_new_in_XXX_version_1_2
in >> other_interesting_data
//! [4]


//! [5]
out = QDataStream(file)
out.setVersion(QDataStream.Qt_4_0)
//! [5]

}
