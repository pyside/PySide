//! [0]
for cert in QSslCertificate.fromPath('C:/ssl/certificate.*.pem', QSsL.Pem, QRegExp.Wildcard):
    print cert.issuerInfo(QSslCertificate.Organization)
//! [0]
