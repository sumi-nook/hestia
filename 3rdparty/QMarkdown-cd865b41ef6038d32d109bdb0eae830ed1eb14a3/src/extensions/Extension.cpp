/*
 * Extension.cpp
 *
 *  Created on: 2013/11/04
 *      Author: mugwort_rc
 */

#include "extensions/Extension.h"

#include <QStringList>

namespace  markdown {

Extension::Extension(const Config &config) :
    config(config)
{}

Extension::~Extension()
{}

QString Extension::getConfig(const QString &key, const QString &default_val) const
{
    if ( this->config.contains(key) ) {
        return this->config[key].at(0);
    }
    return default_val;
}

void Extension::setConfig(const QString &key, const QStringList &value)
{
    this->config[key] = value;
}

} // end of namespace markdown
