/*
 * htmlentitydefs.hpp
 *
 *  Created on: 2013/11/13
 *      Author: mugwort_rc
 */

#ifndef HTMLENTITYDEFS_HPP_
#define HTMLENTITYDEFS_HPP_

#include <map>

#include <QMap>
#include <QString>

namespace markdown{

//! from htmlentitydefs.py
QMap<QChar, QString> codepoint2name = {
    std::make_pair(QChar(0x00c6), "AElig"),    //!< latin capital letter AE = latin capital ligature AE, U+00C6 ISOlat1
    std::make_pair(QChar(0x00c1), "Aacute"),   //!< latin capital letter A with acute, U+00C1 ISOlat1
    std::make_pair(QChar(0x00c2), "Acirc"),    //!< latin capital letter A with circumflex, U+00C2 ISOlat1
    std::make_pair(QChar(0x00c0), "Agrave"),   //!< latin capital letter A with grave = latin capital letter A grave, U+00C0 ISOlat1
    std::make_pair(QChar(0x0391), "Alpha"),    //!< greek capital letter alpha, U+0391
    std::make_pair(QChar(0x00c5), "Aring"),    //!< latin capital letter A with ring above = latin capital letter A ring, U+00C5 ISOlat1
    std::make_pair(QChar(0x00c3), "Atilde"),   //!< latin capital letter A with tilde, U+00C3 ISOlat1
    std::make_pair(QChar(0x00c4), "Auml"),     //!< latin capital letter A with diaeresis, U+00C4 ISOlat1
    std::make_pair(QChar(0x0392), "Beta"),     //!< greek capital letter beta, U+0392
    std::make_pair(QChar(0x00c7), "Ccedil"),   //!< latin capital letter C with cedilla, U+00C7 ISOlat1
    std::make_pair(QChar(0x03a7), "Chi"),      //!< greek capital letter chi, U+03A7
    std::make_pair(QChar(0x2021), "Dagger"),   //!< double dagger, U+2021 ISOpub
    std::make_pair(QChar(0x0394), "Delta"),    //!< greek capital letter delta, U+0394 ISOgrk3
    std::make_pair(QChar(0x00d0), "ETH"),      //!< latin capital letter ETH, U+00D0 ISOlat1
    std::make_pair(QChar(0x00c9), "Eacute"),   //!< latin capital letter E with acute, U+00C9 ISOlat1
    std::make_pair(QChar(0x00ca), "Ecirc"),    //!< latin capital letter E with circumflex, U+00CA ISOlat1
    std::make_pair(QChar(0x00c8), "Egrave"),   //!< latin capital letter E with grave, U+00C8 ISOlat1
    std::make_pair(QChar(0x0395), "Epsilon"),  //!< greek capital letter epsilon, U+0395
    std::make_pair(QChar(0x0397), "Eta"),      //!< greek capital letter eta, U+0397
    std::make_pair(QChar(0x00cb), "Euml"),     //!< latin capital letter E with diaeresis, U+00CB ISOlat1
    std::make_pair(QChar(0x0393), "Gamma"),    //!< greek capital letter gamma, U+0393 ISOgrk3
    std::make_pair(QChar(0x00cd), "Iacute"),   //!< latin capital letter I with acute, U+00CD ISOlat1
    std::make_pair(QChar(0x00ce), "Icirc"),    //!< latin capital letter I with circumflex, U+00CE ISOlat1
    std::make_pair(QChar(0x00cc), "Igrave"),   //!< latin capital letter I with grave, U+00CC ISOlat1
    std::make_pair(QChar(0x0399), "Iota"),     //!< greek capital letter iota, U+0399
    std::make_pair(QChar(0x00cf), "Iuml"),     //!< latin capital letter I with diaeresis, U+00CF ISOlat1
    std::make_pair(QChar(0x039a), "Kappa"),    //!< greek capital letter kappa, U+039A
    std::make_pair(QChar(0x039b), "Lambda"),   //!< greek capital letter lambda, U+039B ISOgrk3
    std::make_pair(QChar(0x039c), "Mu"),       //!< greek capital letter mu, U+039C
    std::make_pair(QChar(0x00d1), "Ntilde"),   //!< latin capital letter N with tilde, U+00D1 ISOlat1
    std::make_pair(QChar(0x039d), "Nu"),       //!< greek capital letter nu, U+039D
    std::make_pair(QChar(0x0152), "OElig"),    //!< latin capital ligature OE, U+0152 ISOlat2
    std::make_pair(QChar(0x00d3), "Oacute"),   //!< latin capital letter O with acute, U+00D3 ISOlat1
    std::make_pair(QChar(0x00d4), "Ocirc"),    //!< latin capital letter O with circumflex, U+00D4 ISOlat1
    std::make_pair(QChar(0x00d2), "Ograve"),   //!< latin capital letter O with grave, U+00D2 ISOlat1
    std::make_pair(QChar(0x03a9), "Omega"),    //!< greek capital letter omega, U+03A9 ISOgrk3
    std::make_pair(QChar(0x039f), "Omicron"),  //!< greek capital letter omicron, U+039F
    std::make_pair(QChar(0x00d8), "Oslash"),   //!< latin capital letter O with stroke = latin capital letter O slash, U+00D8 ISOlat1
    std::make_pair(QChar(0x00d5), "Otilde"),   //!< latin capital letter O with tilde, U+00D5 ISOlat1
    std::make_pair(QChar(0x00d6), "Ouml"),     //!< latin capital letter O with diaeresis, U+00D6 ISOlat1
    std::make_pair(QChar(0x03a6), "Phi"),      //!< greek capital letter phi, U+03A6 ISOgrk3
    std::make_pair(QChar(0x03a0), "Pi"),       //!< greek capital letter pi, U+03A0 ISOgrk3
    std::make_pair(QChar(0x2033), "Prime"),    //!< double prime = seconds = inches, U+2033 ISOtech
    std::make_pair(QChar(0x03a8), "Psi"),      //!< greek capital letter psi, U+03A8 ISOgrk3
    std::make_pair(QChar(0x03a1), "Rho"),      //!< greek capital letter rho, U+03A1
    std::make_pair(QChar(0x0160), "Scaron"),   //!< latin capital letter S with caron, U+0160 ISOlat2
    std::make_pair(QChar(0x03a3), "Sigma"),    //!< greek capital letter sigma, U+03A3 ISOgrk3
    std::make_pair(QChar(0x00de), "THORN"),    //!< latin capital letter THORN, U+00DE ISOlat1
    std::make_pair(QChar(0x03a4), "Tau"),      //!< greek capital letter tau, U+03A4
    std::make_pair(QChar(0x0398), "Theta"),    //!< greek capital letter theta, U+0398 ISOgrk3
    std::make_pair(QChar(0x00da), "Uacute"),   //!< latin capital letter U with acute, U+00DA ISOlat1
    std::make_pair(QChar(0x00db), "Ucirc"),    //!< latin capital letter U with circumflex, U+00DB ISOlat1
    std::make_pair(QChar(0x00d9), "Ugrave"),   //!< latin capital letter U with grave, U+00D9 ISOlat1
    std::make_pair(QChar(0x03a5), "Upsilon"),  //!< greek capital letter upsilon, U+03A5 ISOgrk3
    std::make_pair(QChar(0x00dc), "Uuml"),     //!< latin capital letter U with diaeresis, U+00DC ISOlat1
    std::make_pair(QChar(0x039e), "Xi"),       //!< greek capital letter xi, U+039E ISOgrk3
    std::make_pair(QChar(0x00dd), "Yacute"),   //!< latin capital letter Y with acute, U+00DD ISOlat1
    std::make_pair(QChar(0x0178), "Yuml"),     //!< latin capital letter Y with diaeresis, U+0178 ISOlat2
    std::make_pair(QChar(0x0396), "Zeta"),     //!< greek capital letter zeta, U+0396
    std::make_pair(QChar(0x00e1), "aacute"),   //!< latin small letter a with acute, U+00E1 ISOlat1
    std::make_pair(QChar(0x00e2), "acirc"),    //!< latin small letter a with circumflex, U+00E2 ISOlat1
    std::make_pair(QChar(0x00b4), "acute"),    //!< acute accent = spacing acute, U+00B4 ISOdia
    std::make_pair(QChar(0x00e6), "aelig"),    //!< latin small letter ae = latin small ligature ae, U+00E6 ISOlat1
    std::make_pair(QChar(0x00e0), "agrave"),   //!< latin small letter a with grave = latin small letter a grave, U+00E0 ISOlat1
    std::make_pair(QChar(0x2135), "alefsym"),  //!< alef symbol = first transfinite cardinal, U+2135 NEW
    std::make_pair(QChar(0x03b1), "alpha"),    //!< greek small letter alpha, U+03B1 ISOgrk3
    std::make_pair(QChar(0x0026), "amp"),      //!< ampersand, U+0026 ISOnum
    std::make_pair(QChar(0x2227), "and"),      //!< logical and = wedge, U+2227 ISOtech
    std::make_pair(QChar(0x2220), "ang"),      //!< angle, U+2220 ISOamso
    std::make_pair(QChar(0x00e5), "aring"),    //!< latin small letter a with ring above = latin small letter a ring, U+00E5 ISOlat1
    std::make_pair(QChar(0x2248), "asymp"),    //!< almost equal to = asymptotic to, U+2248 ISOamsr
    std::make_pair(QChar(0x00e3), "atilde"),   //!< latin small letter a with tilde, U+00E3 ISOlat1
    std::make_pair(QChar(0x00e4), "auml"),     //!< latin small letter a with diaeresis, U+00E4 ISOlat1
    std::make_pair(QChar(0x201e), "bdquo"),    //!< double low-9 quotation mark, U+201E NEW
    std::make_pair(QChar(0x03b2), "beta"),     //!< greek small letter beta, U+03B2 ISOgrk3
    std::make_pair(QChar(0x00a6), "brvbar"),   //!< broken bar = broken vertical bar, U+00A6 ISOnum
    std::make_pair(QChar(0x2022), "bull"),     //!< bullet = black small circle, U+2022 ISOpub
    std::make_pair(QChar(0x2229), "cap"),      //!< intersection = cap, U+2229 ISOtech
    std::make_pair(QChar(0x00e7), "ccedil"),   //!< latin small letter c with cedilla, U+00E7 ISOlat1
    std::make_pair(QChar(0x00b8), "cedil"),    //!< cedilla = spacing cedilla, U+00B8 ISOdia
    std::make_pair(QChar(0x00a2), "cent"),     //!< cent sign, U+00A2 ISOnum
    std::make_pair(QChar(0x03c7), "chi"),      //!< greek small letter chi, U+03C7 ISOgrk3
    std::make_pair(QChar(0x02c6), "circ"),     //!< modifier letter circumflex accent, U+02C6 ISOpub
    std::make_pair(QChar(0x2663), "clubs"),    //!< black club suit = shamrock, U+2663 ISOpub
    std::make_pair(QChar(0x2245), "cong"),     //!< approximately equal to, U+2245 ISOtech
    std::make_pair(QChar(0x00a9), "copy"),     //!< copyright sign, U+00A9 ISOnum
    std::make_pair(QChar(0x21b5), "crarr"),    //!< downwards arrow with corner leftwards = carriage return, U+21B5 NEW
    std::make_pair(QChar(0x222a), "cup"),      //!< union = cup, U+222A ISOtech
    std::make_pair(QChar(0x00a4), "curren"),   //!< currency sign, U+00A4 ISOnum
    std::make_pair(QChar(0x21d3), "dArr"),     //!< downwards double arrow, U+21D3 ISOamsa
    std::make_pair(QChar(0x2020), "dagger"),   //!< dagger, U+2020 ISOpub
    std::make_pair(QChar(0x2193), "darr"),     //!< downwards arrow, U+2193 ISOnum
    std::make_pair(QChar(0x00b0), "deg"),      //!< degree sign, U+00B0 ISOnum
    std::make_pair(QChar(0x03b4), "delta"),    //!< greek small letter delta, U+03B4 ISOgrk3
    std::make_pair(QChar(0x2666), "diams"),    //!< black diamond suit, U+2666 ISOpub
    std::make_pair(QChar(0x00f7), "divide"),   //!< division sign, U+00F7 ISOnum
    std::make_pair(QChar(0x00e9), "eacute"),   //!< latin small letter e with acute, U+00E9 ISOlat1
    std::make_pair(QChar(0x00ea), "ecirc"),    //!< latin small letter e with circumflex, U+00EA ISOlat1
    std::make_pair(QChar(0x00e8), "egrave"),   //!< latin small letter e with grave, U+00E8 ISOlat1
    std::make_pair(QChar(0x2205), "empty"),    //!< empty set = null set = diameter, U+2205 ISOamso
    std::make_pair(QChar(0x2003), "emsp"),     //!< em space, U+2003 ISOpub
    std::make_pair(QChar(0x2002), "ensp"),     //!< en space, U+2002 ISOpub
    std::make_pair(QChar(0x03b5), "epsilon"),  //!< greek small letter epsilon, U+03B5 ISOgrk3
    std::make_pair(QChar(0x2261), "equiv"),    //!< identical to, U+2261 ISOtech
    std::make_pair(QChar(0x03b7), "eta"),      //!< greek small letter eta, U+03B7 ISOgrk3
    std::make_pair(QChar(0x00f0), "eth"),      //!< latin small letter eth, U+00F0 ISOlat1
    std::make_pair(QChar(0x00eb), "euml"),     //!< latin small letter e with diaeresis, U+00EB ISOlat1
    std::make_pair(QChar(0x20ac), "euro"),     //!< euro sign, U+20AC NEW
    std::make_pair(QChar(0x2203), "exist"),    //!< there exists, U+2203 ISOtech
    std::make_pair(QChar(0x0192), "fnof"),     //!< latin small f with hook = function = florin, U+0192 ISOtech
    std::make_pair(QChar(0x2200), "forall"),   //!< for all, U+2200 ISOtech
    std::make_pair(QChar(0x00bd), "frac12"),   //!< vulgar fraction one half = fraction one half, U+00BD ISOnum
    std::make_pair(QChar(0x00bc), "frac14"),   //!< vulgar fraction one quarter = fraction one quarter, U+00BC ISOnum
    std::make_pair(QChar(0x00be), "frac34"),   //!< vulgar fraction three quarters = fraction three quarters, U+00BE ISOnum
    std::make_pair(QChar(0x2044), "frasl"),    //!< fraction slash, U+2044 NEW
    std::make_pair(QChar(0x03b3), "gamma"),    //!< greek small letter gamma, U+03B3 ISOgrk3
    std::make_pair(QChar(0x2265), "ge"),       //!< greater-than or equal to, U+2265 ISOtech
    std::make_pair(QChar(0x003e), "gt"),       //!< greater-than sign, U+003E ISOnum
    std::make_pair(QChar(0x21d4), "hArr"),     //!< left right double arrow, U+21D4 ISOamsa
    std::make_pair(QChar(0x2194), "harr"),     //!< left right arrow, U+2194 ISOamsa
    std::make_pair(QChar(0x2665), "hearts"),   //!< black heart suit = valentine, U+2665 ISOpub
    std::make_pair(QChar(0x2026), "hellip"),   //!< horizontal ellipsis = three dot leader, U+2026 ISOpub
    std::make_pair(QChar(0x00ed), "iacute"),   //!< latin small letter i with acute, U+00ED ISOlat1
    std::make_pair(QChar(0x00ee), "icirc"),    //!< latin small letter i with circumflex, U+00EE ISOlat1
    std::make_pair(QChar(0x00a1), "iexcl"),    //!< inverted exclamation mark, U+00A1 ISOnum
    std::make_pair(QChar(0x00ec), "igrave"),   //!< latin small letter i with grave, U+00EC ISOlat1
    std::make_pair(QChar(0x2111), "image"),    //!< blackletter capital I = imaginary part, U+2111 ISOamso
    std::make_pair(QChar(0x221e), "infin"),    //!< infinity, U+221E ISOtech
    std::make_pair(QChar(0x222b), "int"),      //!< integral, U+222B ISOtech
    std::make_pair(QChar(0x03b9), "iota"),     //!< greek small letter iota, U+03B9 ISOgrk3
    std::make_pair(QChar(0x00bf), "iquest"),   //!< inverted question mark = turned question mark, U+00BF ISOnum
    std::make_pair(QChar(0x2208), "isin"),     //!< element of, U+2208 ISOtech
    std::make_pair(QChar(0x00ef), "iuml"),     //!< latin small letter i with diaeresis, U+00EF ISOlat1
    std::make_pair(QChar(0x03ba), "kappa"),    //!< greek small letter kappa, U+03BA ISOgrk3
    std::make_pair(QChar(0x21d0), "lArr"),     //!< leftwards double arrow, U+21D0 ISOtech
    std::make_pair(QChar(0x03bb), "lambda"),   //!< greek small letter lambda, U+03BB ISOgrk3
    std::make_pair(QChar(0x2329), "lang"),     //!< left-pointing angle bracket = bra, U+2329 ISOtech
    std::make_pair(QChar(0x00ab), "laquo"),    //!< left-pointing double angle quotation mark = left pointing guillemet, U+00AB ISOnum
    std::make_pair(QChar(0x2190), "larr"),     //!< leftwards arrow, U+2190 ISOnum
    std::make_pair(QChar(0x2308), "lceil"),    //!< left ceiling = apl upstile, U+2308 ISOamsc
    std::make_pair(QChar(0x201c), "ldquo"),    //!< left double quotation mark, U+201C ISOnum
    std::make_pair(QChar(0x2264), "le"),       //!< less-than or equal to, U+2264 ISOtech
    std::make_pair(QChar(0x230a), "lfloor"),   //!< left floor = apl downstile, U+230A ISOamsc
    std::make_pair(QChar(0x2217), "lowast"),   //!< asterisk operator, U+2217 ISOtech
    std::make_pair(QChar(0x25ca), "loz"),      //!< lozenge, U+25CA ISOpub
    std::make_pair(QChar(0x200e), "lrm"),      //!< left-to-right mark, U+200E NEW RFC 2070
    std::make_pair(QChar(0x2039), "lsaquo"),   //!< single left-pointing angle quotation mark, U+2039 ISO proposed
    std::make_pair(QChar(0x2018), "lsquo"),    //!< left single quotation mark, U+2018 ISOnum
    std::make_pair(QChar(0x003c), "lt"),       //!< less-than sign, U+003C ISOnum
    std::make_pair(QChar(0x00af), "macr"),     //!< macron = spacing macron = overline = APL overbar, U+00AF ISOdia
    std::make_pair(QChar(0x2014), "mdash"),    //!< em dash, U+2014 ISOpub
    std::make_pair(QChar(0x00b5), "micro"),    //!< micro sign, U+00B5 ISOnum
    std::make_pair(QChar(0x00b7), "middot"),   //!< middle dot = Georgian comma = Greek middle dot, U+00B7 ISOnum
    std::make_pair(QChar(0x2212), "minus"),    //!< minus sign, U+2212 ISOtech
    std::make_pair(QChar(0x03bc), "mu"),       //!< greek small letter mu, U+03BC ISOgrk3
    std::make_pair(QChar(0x2207), "nabla"),    //!< nabla = backward difference, U+2207 ISOtech
    std::make_pair(QChar(0x00a0), "nbsp"),     //!< no-break space = non-breaking space, U+00A0 ISOnum
    std::make_pair(QChar(0x2013), "ndash"),    //!< en dash, U+2013 ISOpub
    std::make_pair(QChar(0x2260), "ne"),       //!< not equal to, U+2260 ISOtech
    std::make_pair(QChar(0x220b), "ni"),       //!< contains as member, U+220B ISOtech
    std::make_pair(QChar(0x00ac), "not"),      //!< not sign, U+00AC ISOnum
    std::make_pair(QChar(0x2209), "notin"),    //!< not an element of, U+2209 ISOtech
    std::make_pair(QChar(0x2284), "nsub"),     //!< not a subset of, U+2284 ISOamsn
    std::make_pair(QChar(0x00f1), "ntilde"),   //!< latin small letter n with tilde, U+00F1 ISOlat1
    std::make_pair(QChar(0x03bd), "nu"),       //!< greek small letter nu, U+03BD ISOgrk3
    std::make_pair(QChar(0x00f3), "oacute"),   //!< latin small letter o with acute, U+00F3 ISOlat1
    std::make_pair(QChar(0x00f4), "ocirc"),    //!< latin small letter o with circumflex, U+00F4 ISOlat1
    std::make_pair(QChar(0x0153), "oelig"),    //!< latin small ligature oe, U+0153 ISOlat2
    std::make_pair(QChar(0x00f2), "ograve"),   //!< latin small letter o with grave, U+00F2 ISOlat1
    std::make_pair(QChar(0x203e), "oline"),    //!< overline = spacing overscore, U+203E NEW
    std::make_pair(QChar(0x03c9), "omega"),    //!< greek small letter omega, U+03C9 ISOgrk3
    std::make_pair(QChar(0x03bf), "omicron"),  //!< greek small letter omicron, U+03BF NEW
    std::make_pair(QChar(0x2295), "oplus"),    //!< circled plus = direct sum, U+2295 ISOamsb
    std::make_pair(QChar(0x2228), "or"),       //!< logical or = vee, U+2228 ISOtech
    std::make_pair(QChar(0x00aa), "ordf"),     //!< feminine ordinal indicator, U+00AA ISOnum
    std::make_pair(QChar(0x00ba), "ordm"),     //!< masculine ordinal indicator, U+00BA ISOnum
    std::make_pair(QChar(0x00f8), "oslash"),   //!< latin small letter o with stroke, = latin small letter o slash, U+00F8 ISOlat1
    std::make_pair(QChar(0x00f5), "otilde"),   //!< latin small letter o with tilde, U+00F5 ISOlat1
    std::make_pair(QChar(0x2297), "otimes"),   //!< circled times = vector product, U+2297 ISOamsb
    std::make_pair(QChar(0x00f6), "ouml"),     //!< latin small letter o with diaeresis, U+00F6 ISOlat1
    std::make_pair(QChar(0x00b6), "para"),     //!< pilcrow sign = paragraph sign, U+00B6 ISOnum
    std::make_pair(QChar(0x2202), "part"),     //!< partial differential, U+2202 ISOtech
    std::make_pair(QChar(0x2030), "permil"),   //!< per mille sign, U+2030 ISOtech
    std::make_pair(QChar(0x22a5), "perp"),     //!< up tack = orthogonal to = perpendicular, U+22A5 ISOtech
    std::make_pair(QChar(0x03c6), "phi"),      //!< greek small letter phi, U+03C6 ISOgrk3
    std::make_pair(QChar(0x03c0), "pi"),       //!< greek small letter pi, U+03C0 ISOgrk3
    std::make_pair(QChar(0x03d6), "piv"),      //!< greek pi symbol, U+03D6 ISOgrk3
    std::make_pair(QChar(0x00b1), "plusmn"),   //!< plus-minus sign = plus-or-minus sign, U+00B1 ISOnum
    std::make_pair(QChar(0x00a3), "pound"),    //!< pound sign, U+00A3 ISOnum
    std::make_pair(QChar(0x2032), "prime"),    //!< prime = minutes = feet, U+2032 ISOtech
    std::make_pair(QChar(0x220f), "prod"),     //!< n-ary product = product sign, U+220F ISOamsb
    std::make_pair(QChar(0x221d), "prop"),     //!< proportional to, U+221D ISOtech
    std::make_pair(QChar(0x03c8), "psi"),      //!< greek small letter psi, U+03C8 ISOgrk3
    std::make_pair(QChar(0x0022), "quot"),     //!< quotation mark = APL quote, U+0022 ISOnum
    std::make_pair(QChar(0x21d2), "rArr"),     //!< rightwards double arrow, U+21D2 ISOtech
    std::make_pair(QChar(0x221a), "radic"),    //!< square root = radical sign, U+221A ISOtech
    std::make_pair(QChar(0x232a), "rang"),     //!< right-pointing angle bracket = ket, U+232A ISOtech
    std::make_pair(QChar(0x00bb), "raquo"),    //!< right-pointing double angle quotation mark = right pointing guillemet, U+00BB ISOnum
    std::make_pair(QChar(0x2192), "rarr"),     //!< rightwards arrow, U+2192 ISOnum
    std::make_pair(QChar(0x2309), "rceil"),    //!< right ceiling, U+2309 ISOamsc
    std::make_pair(QChar(0x201d), "rdquo"),    //!< right double quotation mark, U+201D ISOnum
    std::make_pair(QChar(0x211c), "real"),     //!< blackletter capital R = real part symbol, U+211C ISOamso
    std::make_pair(QChar(0x00ae), "reg"),      //!< registered sign = registered trade mark sign, U+00AE ISOnum
    std::make_pair(QChar(0x230b), "rfloor"),   //!< right floor, U+230B ISOamsc
    std::make_pair(QChar(0x03c1), "rho"),      //!< greek small letter rho, U+03C1 ISOgrk3
    std::make_pair(QChar(0x200f), "rlm"),      //!< right-to-left mark, U+200F NEW RFC 2070
    std::make_pair(QChar(0x203a), "rsaquo"),   //!< single right-pointing angle quotation mark, U+203A ISO proposed
    std::make_pair(QChar(0x2019), "rsquo"),    //!< right single quotation mark, U+2019 ISOnum
    std::make_pair(QChar(0x201a), "sbquo"),    //!< single low-9 quotation mark, U+201A NEW
    std::make_pair(QChar(0x0161), "scaron"),   //!< latin small letter s with caron, U+0161 ISOlat2
    std::make_pair(QChar(0x22c5), "sdot"),     //!< dot operator, U+22C5 ISOamsb
    std::make_pair(QChar(0x00a7), "sect"),     //!< section sign, U+00A7 ISOnum
    std::make_pair(QChar(0x00ad), "shy"),      //!< soft hyphen = discretionary hyphen, U+00AD ISOnum
    std::make_pair(QChar(0x03c3), "sigma"),    //!< greek small letter sigma, U+03C3 ISOgrk3
    std::make_pair(QChar(0x03c2), "sigmaf"),   //!< greek small letter final sigma, U+03C2 ISOgrk3
    std::make_pair(QChar(0x223c), "sim"),      //!< tilde operator = varies with = similar to, U+223C ISOtech
    std::make_pair(QChar(0x2660), "spades"),   //!< black spade suit, U+2660 ISOpub
    std::make_pair(QChar(0x2282), "sub"),      //!< subset of, U+2282 ISOtech
    std::make_pair(QChar(0x2286), "sube"),     //!< subset of or equal to, U+2286 ISOtech
    std::make_pair(QChar(0x2211), "sum"),      //!< n-ary sumation, U+2211 ISOamsb
    std::make_pair(QChar(0x2283), "sup"),      //!< superset of, U+2283 ISOtech
    std::make_pair(QChar(0x00b9), "sup1"),     //!< superscript one = superscript digit one, U+00B9 ISOnum
    std::make_pair(QChar(0x00b2), "sup2"),     //!< superscript two = superscript digit two = squared, U+00B2 ISOnum
    std::make_pair(QChar(0x00b3), "sup3"),     //!< superscript three = superscript digit three = cubed, U+00B3 ISOnum
    std::make_pair(QChar(0x2287), "supe"),     //!< superset of or equal to, U+2287 ISOtech
    std::make_pair(QChar(0x00df), "szlig"),    //!< latin small letter sharp s = ess-zed, U+00DF ISOlat1
    std::make_pair(QChar(0x03c4), "tau"),      //!< greek small letter tau, U+03C4 ISOgrk3
    std::make_pair(QChar(0x2234), "there4"),   //!< therefore, U+2234 ISOtech
    std::make_pair(QChar(0x03b8), "theta"),    //!< greek small letter theta, U+03B8 ISOgrk3
    std::make_pair(QChar(0x03d1), "thetasym"), //!< greek small letter theta symbol, U+03D1 NEW
    std::make_pair(QChar(0x2009), "thinsp"),   //!< thin space, U+2009 ISOpub
    std::make_pair(QChar(0x00fe), "thorn"),    //!< latin small letter thorn with, U+00FE ISOlat1
    std::make_pair(QChar(0x02dc), "tilde"),    //!< small tilde, U+02DC ISOdia
    std::make_pair(QChar(0x00d7), "times"),    //!< multiplication sign, U+00D7 ISOnum
    std::make_pair(QChar(0x2122), "trade"),    //!< trade mark sign, U+2122 ISOnum
    std::make_pair(QChar(0x21d1), "uArr"),     //!< upwards double arrow, U+21D1 ISOamsa
    std::make_pair(QChar(0x00fa), "uacute"),   //!< latin small letter u with acute, U+00FA ISOlat1
    std::make_pair(QChar(0x2191), "uarr"),     //!< upwards arrow, U+2191 ISOnum
    std::make_pair(QChar(0x00fb), "ucirc"),    //!< latin small letter u with circumflex, U+00FB ISOlat1
    std::make_pair(QChar(0x00f9), "ugrave"),   //!< latin small letter u with grave, U+00F9 ISOlat1
    std::make_pair(QChar(0x00a8), "uml"),      //!< diaeresis = spacing diaeresis, U+00A8 ISOdia
    std::make_pair(QChar(0x03d2), "upsih"),    //!< greek upsilon with hook symbol, U+03D2 NEW
    std::make_pair(QChar(0x03c5), "upsilon"),  //!< greek small letter upsilon, U+03C5 ISOgrk3
    std::make_pair(QChar(0x00fc), "uuml"),     //!< latin small letter u with diaeresis, U+00FC ISOlat1
    std::make_pair(QChar(0x2118), "weierp"),   //!< script capital P = power set = Weierstrass p, U+2118 ISOamso
    std::make_pair(QChar(0x03be), "xi"),       //!< greek small letter xi, U+03BE ISOgrk3
    std::make_pair(QChar(0x00fd), "yacute"),   //!< latin small letter y with acute, U+00FD ISOlat1
    std::make_pair(QChar(0x00a5), "yen"),      //!< yen sign = yuan sign, U+00A5 ISOnum
    std::make_pair(QChar(0x00ff), "yuml"),     //!< latin small letter y with diaeresis, U+00FF ISOlat1
    std::make_pair(QChar(0x03b6), "zeta"),     //!< greek small letter zeta, U+03B6 ISOgrk3
    std::make_pair(QChar(0x200d), "zwj"),      //!< zero width joiner, U+200D NEW RFC 2070
    std::make_pair(QChar(0x200c), "zwnj"),     //!< zero width non-joiner, U+200C NEW RFC 2070
};

} // end of namespace markdown

#endif // HTMLENTITYDEFS_HPP_
