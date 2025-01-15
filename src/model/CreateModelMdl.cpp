#include "CreateModelMdl.hpp"

#include "DBManager.hpp"

// Constructor
CreateModelMdl::CreateModelMdl(){
    dBManager = DBManager::getInstance();
}

// Destructor
CreateModelMdl::~CreateModelMdl(){
    // Do not delete dBManager as it is managed by DBManager class itself
}

bool CreateModelMdl::isModelNameExists(const QString modelName){
    // dBManager->
    return true;
}

// Getter ve Setter fonksiyonları

const QString& CreateModelMdl::modelName() const {
    return m_modelName;
}

void CreateModelMdl::setModelName(const QString& modelName) {
    m_modelName = modelName;
}

const QString& CreateModelMdl::defaultPair() const {
    return m_defaultPair;
}

void CreateModelMdl::setDefaultPair(const QString& defaultPair) {
    m_defaultPair = defaultPair;
}

const QString& CreateModelMdl::windowSize() const {
    return m_windowSize;
}

void CreateModelMdl::setWindowSize(const QString& windowSize) {
    m_windowSize = windowSize;
}

const QString& CreateModelMdl::modelType() const {
    return m_modelType;
}

void CreateModelMdl::setModelType(const QString& modelType) {
    m_modelType = modelType;
}

const QString& CreateModelMdl::defaultInterval() const {
    return m_defaultInterval;
}

void CreateModelMdl::setDefaultInterval(const QString& defaultInterval) {
    m_defaultInterval = defaultInterval;
}
