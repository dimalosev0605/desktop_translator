#ifndef REMOTEFILESDATAMODEL_H
#define REMOTEFILESDATAMODEL_H

#include "filesdatamodelbase.h"
#include <QDebug>

class RemoteFilesDataModel: public FilesDataModelBase
{
    Q_OBJECT
public:
    explicit RemoteFilesDataModel(QObject* parent = nullptr);

public slots:
    void receive_list_of_files(const QString& list);
};

#endif // REMOTEFILESDATAMODEL_H
