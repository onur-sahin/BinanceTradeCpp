#include "PullDataCoord.hpp"
#include "PullDataWidget.hpp"
#include "PullDataVM.hpp"


PullDataCoord::PullDataCoord(QObject *parent)
    : QObject(parent)
    , m_view     ( new PullDataWidget() )
    , m_viewmodel( new PullDataVM()     )
    {

    }