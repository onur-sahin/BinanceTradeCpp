#pragma once

#include <QString>

class DBManager;

class CreateModelMdl {
public:
    CreateModelMdl();
    ~CreateModelMdl();

    bool isModelNameExists(const QString modelName);

    // Getter ve Setter fonksiyonları
    const QString& modelName() const;  // Getter
    void setModelName(const QString& modelName);  // Setter

    const QString& defaultPair() const;  // Getter
    void setDefaultPair(const QString& defaultPair);  // Setter

    const QString& windowSize() const;  // Getter
    void setWindowSize(const QString& windowSize);  // Setter

    const QString& modelType() const;  // Getter
    void setModelType(const QString& modelType);  // Setter

    const QString& defaultInterval() const;  // Getter
    void setDefaultInterval(const QString& defaultInterval);  // Setter

private:
    DBManager *dBManager;

    QString m_modelName;
    QString m_defaultPair;
    QString m_windowSize;
    QString m_modelType;
    QString m_defaultInterval;
};
