/*
 * Extension.h
 *
 *  Created on: 2013/11/04
 *      Author: mugwort_rc
 */

#ifndef EXTENSION_H_
#define EXTENSION_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <QMap>
#include <QString>

namespace markdown{

class Markdown;  //!< forward declaration

/*!
 * Base class for extensions to subclass.
 */
class Extension
{
public:
    typedef std::shared_ptr<Extension> Ptr;
    typedef QMap<QString, QStringList> Config;

public:
    /*!
     * Create an instance of an Extention.
     *
     * Keyword arguments:
     *
     * * configs: A dict of configuration setting used by an Extension.
     */
    Extension(const Config &config=Config());
    virtual ~Extension(void);

    /*!
     * Return a setting for the given key or an empty string.
     */
    QString getConfig(const QString &key, const QString &default_val=QString()) const;
    /*!
     * Return all configs settings as a dict.
     */
    Config getConfigs(void) const
    { return this->config; }
    /*!
     * Set a config setting for `key` with the given `value`.
     */
    void setConfig(const QString &key, const QStringList &value);

    virtual void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/) = 0;

    virtual void reset(void)
    {}

private:
    Config config;

};

} // end of namespace markdown

#endif // EXTENSION_H_
