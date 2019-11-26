#ifndef LOCALFILESDATAMODEL_H
#define LOCALFILESDATAMODEL_H

#include "filesdatamodelbase.h"

class LocalFilesDataModel: public FilesDataModelBase
{
    Q_OBJECT
    void retrieve_user_files();

public:
    explicit LocalFilesDataModel(QObject* parent = nullptr);

public slots:
    void delete_file(int index);
};

#endif // LOCALFILESDATAMODEL_H
