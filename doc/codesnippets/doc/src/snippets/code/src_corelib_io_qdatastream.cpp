void wrapInFunction()
{

//! [0]
file_ = QFile("file.dat")
file_.open(QIODevice.WriteOnly)
# we will serialize the data into the file
out = QDataStream(file_)
# serialize a string
out.writeQString("the answer is")
# serialize an integer
out.writeInt32(42)
//! [0]


//! [1]
file_ = QFile("file.dat")
file_.open(QIODevice.ReadOnly)
# read the data serialized from the file
i = QDataStream(file_)
string = ''
a = 0
# extract "the answer is" and 42
string = i.readQString()
a = i.readInt32()
//! [1]


//! [2]
stream.setVersion(QDataStream.Qt_4_0)
//! [2]


//! [3]
file_ = QFile("file.xxx")
file_.open(QIODevice.WriteOnly)
out = QDataStream(file_)

# Write a header with a "magic number" and a version
out.writeInt32(0xA0B0C0D0)
out.writeInt32(123)

out.setVersion(QDataStream.Qt_4_0)

// Write the data
out << lots_of_interesting_data
//! [3]


//! [4]
file_ = QFile("file.xxx")
file_.open(QIODevice.ReadOnly)
i = QDataStream(file_)

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
    in_.setVersion(QDataStream.Qt_3_2)
else:
    in_.setVersion(QDataStream.Qt_4_0)

// Read the data
in_ >> lots_of_interesting_data
if version >= 120:
    in_ >> data_new_in_XXX_version_1_2
in_ >> other_interesting_data
//! [4]


//! [5]
out = QDataStream(file_)
out.setVersion(QDataStream.Qt_4_0)
//! [5]

}
