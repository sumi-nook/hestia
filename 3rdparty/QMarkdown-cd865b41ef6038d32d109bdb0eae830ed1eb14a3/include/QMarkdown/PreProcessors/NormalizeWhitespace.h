#ifndef NORMALIZEWHITESPACE_H
#define NORMALIZEWHITESPACE_H

#include "PreProcessors.h"

namespace markdown
{

/*!
 * Normalize whitespace for consistant parsing.
 */
class NormalizeWhitespace : public PreProcessor
{
public:
    using PreProcessor::PreProcessor;

    virtual ~NormalizeWhitespace(void);

    QStringList run(const QStringList &lines);

};

} // namespace markdown

#endif // NORMALIZEWHITESPACE_H
