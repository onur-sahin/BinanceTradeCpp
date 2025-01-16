#include "PullDataCoord.hpp"
#include "PullDataVM.hpp"
#include "PullDataWidget.hpp"

PullDataCoord::PullDataCoord(QObject *parent)
    : QObject(parent)
    , m_view     ( new PullDataWidget() )
    , m_viewmodel( new PullDataVM()     )
    {

    }