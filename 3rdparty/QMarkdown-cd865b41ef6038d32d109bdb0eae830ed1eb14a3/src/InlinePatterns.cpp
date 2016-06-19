/*
 * InlinePatterns.cpp
 *
 *  Created on: 2013/10/28
 *      Author: mugwort_rc
 */

#include "InlinePatterns.h"

#include <utility>

#include <boost/algorithm/string.hpp>

#include <QPair>
#include <QSet>

#include "Markdown.h"
#include "pypp.hpp"

#include "InlinePatterns/common.h"
#include "InlinePatterns/BacktickPattern.h"
#include "InlinePatterns/EscapePattern.h"
#include "InlinePatterns/LinkPattern.h"
#include "InlinePatterns/AutolinkPattern.h"
#include "InlinePatterns/AutomailPattern.h"
#include "InlinePatterns/SimpleTagPattern.h"
#include "InlinePatterns/HtmlPattern.h"
#include "InlinePatterns/SimpleTextPattern.h"

namespace markdown{

//! Set values of an element based on attribute definitions ({@id=123}).

Pattern::Pattern(const QString &pattern, const std::weak_ptr<Markdown> &markdown_instance) :
    pattern(pattern), compiled_re(QString("^(.*?)%1(.*)$").arg(pattern), QRegularExpression::DotMatchesEverythingOption | QRegularExpression::UseUnicodePropertiesOption),
    //! Api for Markdown to pass safe_mode into instance
    safe_mode(false), markdown(markdown_instance)
{}

QString Pattern::unescape(const QString &text)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    TreeProcessor::StashNodes stash;
    if ( markdown->treeprocessors.exists("inline") ) {
        stash = markdown->treeprocessors["inline"]->stashed_nodes;
    } else {
        return text;
    }
    auto get_stash = [&](const QRegularExpressionMatch &m) -> QString {
        QString id = m.captured(1);
        if ( stash.contains(id) ) {
            boost::optional<QString> str;
            boost::optional<Element> node;
            std::tie(str, node) = stash[id];
            if ( str ) {
                return *str;
            }
            return itertext(*node);
        }
        return QString();
    };
    return pypp::re::sub(util::INLINE_PLACEHOLDER_RE, get_stash, text);
}


OrderedDictPatterns build_inlinepatterns(const std::shared_ptr<Markdown> &md_instance)
{
    OrderedDictPatterns inlinePatterns;
    inlinePatterns.append("backtick", std::shared_ptr<Pattern>(new BacktickPattern(BACKTICK_RE)));
    inlinePatterns.append("escape", std::shared_ptr<Pattern>(new EscapePattern(ESCAPE_RE, md_instance)));
    inlinePatterns.append("reference", std::shared_ptr<Pattern>(new ReferencePattern(REFERENCE_RE, md_instance)));
    inlinePatterns.append("link", std::shared_ptr<Pattern>(new LinkPattern(LINK_RE, md_instance)));
    inlinePatterns.append("image_link", std::shared_ptr<Pattern>(new ImagePattern(IMAGE_LINK_RE, md_instance)));
    inlinePatterns.append("image_reference", std::shared_ptr<Pattern>(new ImageReferencePattern(IMAGE_REFERENCE_RE, md_instance)));
    inlinePatterns.append("short_reference", std::shared_ptr<Pattern>(new ReferencePattern(SHORT_REF_RE, md_instance)));
    inlinePatterns.append("autolink", std::shared_ptr<Pattern>(new AutolinkPattern(AUTOLINK_RE, md_instance)));
    inlinePatterns.append("automail", std::shared_ptr<Pattern>(new AutomailPattern(AUTOMAIL_RE, md_instance)));
    inlinePatterns.append("linebreak", std::shared_ptr<Pattern>(new SubstituteTagPattern(LINE_BREAK_RE, "br")));
    if ( md_instance->safeMode() != Markdown::escape_mode ) {
        inlinePatterns.append("html", std::shared_ptr<Pattern>(new HtmlPattern(HTML_RE, md_instance)));
    }
    inlinePatterns.append("entity", std::shared_ptr<Pattern>(new HtmlPattern(ENTITY_RE, md_instance)));
    inlinePatterns.append("not_strong", std::shared_ptr<Pattern>(new SimpleTextPattern(NOT_STRONG_RE)));
    inlinePatterns.append("em_strong", std::shared_ptr<Pattern>(new DoubleTagPattern(EM_STRONG_RE, "strong,em")));
    inlinePatterns.append("strong_em", std::shared_ptr<Pattern>(new DoubleTagPattern(STRONG_EM_RE, "em,strong")));
    inlinePatterns.append("strong", std::shared_ptr<Pattern>(new SimpleTagPattern(STRONG_RE, "strong")));
    inlinePatterns.append("emphasis", std::shared_ptr<Pattern>(new SimpleTagPattern(EMPHASIS_RE, "em")));
    if ( md_instance->smart_emphasis() ) {
        inlinePatterns.append("emphasis2", std::shared_ptr<Pattern>(new SimpleTagPattern(SMART_EMPHASIS_RE, "em")));
    } else {
        inlinePatterns.append("emphasis2", std::shared_ptr<Pattern>(new SimpleTagPattern(EMPHASIS_2_RE, "em")));
    }
    return inlinePatterns;
}

} // end of namespace markdown
