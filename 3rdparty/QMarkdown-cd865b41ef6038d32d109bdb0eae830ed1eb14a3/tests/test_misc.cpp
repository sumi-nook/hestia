#include "test_misc.h"

#include <QDebug>
#include <QTest>

TestMISC::TestMISC()
{

}

TestMISC::~TestMISC()
{

}

void TestMISC::initTestCase()
{

}

void TestMISC::cleanupTestCase()
{

}

void TestMISC::init()
{
    this->md = markdown::create_Markdown();
}

void TestMISC::cleanup()
{

}

void TestMISC::CRLF_line_ends()
{
    QString converted = this->md->convert(
                "foo\r" "\n"
                "\r" "\n"
                "<div>\r" "\n"
                "bar\r" "\n"
                "</div>\r" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>foo</p>" "\n"
                     "<div>" "\n"
                     "bar" "\n"
                     "</div>"));

}

void TestMISC::adjacent_headers()
{
    QString converted = this->md->convert(
                "# this is a huge header #" "\n"
                "## this is a smaller header ##" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>this is a huge header</h1>" "\n"
                     "<h2>this is a smaller header</h2>"));
}

void TestMISC::amp_in_url()
{
    QString converted = this->md->convert(
                "[link](http://www.freewisdom.org/this&that)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://www.freewisdom.org/this&amp;that">link</a></p>)"));
}

void TestMISC::ampersand()
{
    QString converted = this->md->convert(
                "&" "\n"
                "" "\n"
                "AT&T" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>&amp;</p>" "\n"
                     "<p>AT&amp;T</p>"));
}

void TestMISC::arabic()
{
    QString converted = this->md->convert(
                "" "\n"
                "بايثون" "\n"
                "=====" "\n"
                "" "\n"
                "**بايثون** لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (OOP) وقابلة للتطوير بالإضافة إلى أنها مجانية و مفتوحة المصدر. صُنفت بالأساس كلغة تفسيرية ، بايثون مصممة أصلاً للأداء بعض المهام الخاصة أو المحدودة. إلا أنه يمكن استخدامها بايثون لإنجاز المشاريع الضخمه كأي لغة برمجية أخرى،  غالباً ما يُنصح المبتدئين في ميدان البرمجة بتعلم هذه اللغة لأنها من بين أسهل اللغات البرمجية تعلماً." "\n"
                "" "\n"
                R"(نشأت بايثون في مركز CWI (مركز العلوم والحاسب الآلي) بأمستردام على يد جويدو فان رُزوم. تم تطويرها بلغة C. أطلق فان رُزوم اسم "بايثون" على لغته تعبيرًا عن إعجابه بفِرقَة مسرحية هزلية شهيرة من بريطانيا، كانت تطلق على نفسها اسم مونتي بايثون Monty Python.)" "\n"
                "" "\n"
                "تتميز بايثون بمجتمعها النشط ، كما أن لها الكثير من المكتبات البرمجية ذات الأغراض الخاصة والتي برمجها أشخاص من مجتمع هذه اللغة ، مثلاً مكتبة PyGame التي توفر مجموعه من الوظائف من اجل برمجة الالعاب. ويمكن لبايثون التعامل مع العديد من أنواع قواعد البيانات مثل MySQL وغيره." "\n"
                "" "\n"
                "##أمثلة " "\n"
                "مثال Hello World!" "\n"
                "" "\n"
                R"(    print "Hello World!")" "\n"
                "" "\n"
                "" "\n"
                "مثال لاستخراج المضروب Factorial :" "\n"
                "" "\n"
                "    num = 1" "\n"
                "    x = raw_input('Insert the number please ')" "\n"
                "    x = int(x)" "\n"
                " " "\n"
                "    if x > 69:" "\n"
                "     print 'Math Error !'" "\n"
                "    else:" "\n"
                "     while x > 1:" "\n"
                "      num *= x" "\n"
                "      x = x-1" "\n"
                " " "\n"
                "     print num" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "##وصلات خارجية " "\n"
                "* [الموقع الرسمي للغة بايثون](http://www.python.org)" "\n"
                "" "\n"
                " بذرة حاس " "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>بايثون</h1>" "\n"
                     "<p><strong>بايثون</strong> لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (OOP) وقابلة للتطوير بالإضافة إلى أنها مجانية و مفتوحة المصدر. صُنفت بالأساس كلغة تفسيرية ، بايثون مصممة أصلاً للأداء بعض المهام الخاصة أو المحدودة. إلا أنه يمكن استخدامها بايثون لإنجاز المشاريع الضخمه كأي لغة برمجية أخرى،  غالباً ما يُنصح المبتدئين في ميدان البرمجة بتعلم هذه اللغة لأنها من بين أسهل اللغات البرمجية تعلماً.</p>" "\n"
                     R"(<p>نشأت بايثون في مركز CWI (مركز العلوم والحاسب الآلي) بأمستردام على يد جويدو فان رُزوم. تم تطويرها بلغة C. أطلق فان رُزوم اسم "بايثون" على لغته تعبيرًا عن إعجابه بفِرقَة مسرحية هزلية شهيرة من بريطانيا، كانت تطلق على نفسها اسم مونتي بايثون Monty Python.</p>)" "\n"
                     "<p>تتميز بايثون بمجتمعها النشط ، كما أن لها الكثير من المكتبات البرمجية ذات الأغراض الخاصة والتي برمجها أشخاص من مجتمع هذه اللغة ، مثلاً مكتبة PyGame التي توفر مجموعه من الوظائف من اجل برمجة الالعاب. ويمكن لبايثون التعامل مع العديد من أنواع قواعد البيانات مثل MySQL وغيره.</p>" "\n"
                     "<h2>أمثلة</h2>" "\n"
                     "<p>مثال Hello World!</p>" "\n"
                     R"(<pre><code>print "Hello World!")" "\n"
                     "</code></pre>" "\n"
                     "<p>مثال لاستخراج المضروب Factorial :</p>" "\n"
                     "<pre><code>num = 1" "\n"
                     "x = raw_input('Insert the number please ')" "\n"
                     "x = int(x)" "\n"
                     "" "\n"
                     "if x &gt; 69:" "\n"
                     " print 'Math Error !'" "\n"
                     "else:" "\n"
                     " while x &gt; 1:" "\n"
                     "  num *= x" "\n"
                     "  x = x-1" "\n"
                     "" "\n"
                     " print num" "\n"
                     "</code></pre>" "\n"
                     "<h2>وصلات خارجية</h2>" "\n"
                     "<ul>" "\n"
                     R"(<li><a href="http://www.python.org">الموقع الرسمي للغة بايثون</a></li>)" "\n"
                     "</ul>" "\n"
                     "<p>بذرة حاس </p>"));
}

void TestMISC::attributes2()
{
    QString converted = this->md->convert(
                "{@id=TABLE.OF.CONTENTS}" "\n"
                "" "\n"
                "" "\n"
                "* {@id=TABLEOFCONTENTS}" "\n"
                "" "\n"
                "" "\n"
                "Or in the middle of the text {@id=TABLEOFCONTENTS}" "\n"
                "" "\n"
                "{@id=tableofcontents}" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p id="TABLE.OF.CONTENTS"></p>)" "\n"
                     "<ul>" "\n"
                     R"(<li id="TABLEOFCONTENTS"></li>)" "\n"
                     "</ul>" "\n"
                     R"(<p id="TABLEOFCONTENTS">Or in the middle of the text </p>)" "\n"
                     R"(<p id="tableofcontents"></p>)"));
}

void TestMISC::attributes_image_ref()
{
    QString converted = this->md->convert(
                "![img{@id=foo}][img]" "\n"
                "" "\n"
                "  [img]: http://example.com/i.jpg" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><img alt="img" id="foo" src="http://example.com/i.jpg" /></p>)"));
}

void TestMISC::autolinks_with_asterisks()
{
    QString converted = this->md->convert(
                "<http://some.site/weird*url*thing>" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://some.site/weird*url*thing">http://some.site/weird*url*thing</a></p>)"));
}

void TestMISC::autolinks_with_asterisks_russian()
{
    QString converted = this->md->convert(
                "<http://some.site/нечто*очень*странное>" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://some.site/нечто*очень*странное">http://some.site/нечто*очень*странное</a></p>)"));
}

void TestMISC::backtick_escape()
{
    QString converted = this->md->convert(
                R"(\\`This should not be in code.\\`)" "\n"
                R"(\`This also should not be in code.\`)" "\n"
                R"(\`And finally this should not be in code.`)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p>\`This should not be in code.\`)" "\n"
                     "`This also should not be in code.`" "\n"
                     "`And finally this should not be in code.`</p>"));
}

void TestMISC::bidi()
{
    QString converted = this->md->convert(
                "**Python**（パイソン）は、[Guido van Rossum](http://en.wikipedia.org/wiki/Guido_van_Rossum) によって作られたオープンソースのオブジェクト指向スクリプト言語。[Perl](http://ja.wikipedia.org/wiki/Perl)とともに欧米で広く普及している。イギリスのテレビ局 BBC が製作したコメディ番組『空飛ぶモンティ・パイソン』にちなんで名付けられた。 (Pythonには、爬虫類のニシキヘビの意味があり、Python言語のマスコットやアイコンとして使われることがある。)" "\n"
                "" "\n"
                "|||||||||||||||||||||||||||||THIS SHOULD BE LTR|||||||||||||||||||||||||" "\n"
                "" "\n"
                "|||||||||||||||||||||||||||||THIS SHOULD BE RTL||||||||||||||||||||||||| {@dir=rtl} " "\n"
                "" "\n"
                "" "\n"
                "(**بايثون** لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (THIS SHOULD BE LTR ) وقابلة للتطوير  {@dir=ltr}  بالإضافة إلى أنها مجانية و مفتوح " "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "پایتون زبان برنامه‌نویسی تفسیری و سطح بالا ، شی‌گرا و یک زبان برنامه‌نویسی تفسیری سمت سرور قدرتمند است که توسط گیدو ون روسوم در سال ۱۹۹۰ ساخته شد. این زبان در ویژگی‌ها شبیه پرل، روبی، اسکیم، اسمال‌تاک و تی‌سی‌ال است و از مدیریت خودکار حافظه استفاده می‌کند" "\n"
                "" "\n"
                "Python，是一种面向对象的、直譯式的计算机程序设计语言，也是一种功能强大而完善的通用型语言，已经具有十多年的发展历史，成熟且稳定。" "\n"
                "" "\n"
                "ބްލޫ ވޭލްގެ ދޫ މަތީގައި އެއްފަހަރާ 50 މީހުންނަށް ތިބެވިދާނެވެ. ބޮޑު މަހުގެ ދުލަކީ އެހާމެ ބޮޑު އެއްޗެކެވެ." "\n"
                "" "\n"
                R"(**உருது** 13ஆம் நூற்றாண்டில் உருவான ஒரு இந்தோ-ஐரோப்பிய மொழியாகும். உருது, ஹிந்தியுடன் சேர்த்து "ஹிந்துஸ்தானி" என அழைக்கப்படுகின்றது. மண்டரின், ஆங்கிலம் ஆகியவற்றுக்கு அடுத்தபடியாக மூன்றாவது கூடிய அளவு மக்களால் புரிந்து கொள்ளப்படக்கூடியது ஹிந்துஸ்தானியேயாகும். தாய் மொழியாகப் பேசுபவர்கள் எண்ணிக்கையின் அடிப்படையில் உருது உலகின் 20 ஆவது பெரிய மொழியாகும். 6 கோடி மக்கள் இதனைத் தாய் மொழியாகக் கொண்டுள்ளார்கள். இரண்டாவது மொழியாகக் கொண்டுள்ளவர்கள் உட்பட 11 கோடிப் பேர் இதனைப் பேசுகிறார்கள். உருது பாகிஸ்தானின் அரசகரும மொழியாகவும், இந்தியாவின் அரசகரும மொழிகளுள் ஒன்றாகவும் விளங்குகிறது.)" "\n"
                "" "\n"
                "اردو ہندوآریائی زبانوں کی ہندويورپی شاخ کی ایک زبان ہے جو تيرھويں صدی ميں بر صغير ميں پيدا ہوئی ـ اردو پاکستان کی سرکاری زبان ہے اور بھارت کی سرکاری زبانوں ميں سے ايک ہے۔ اردو بھارت ميں 5 کروڑ اور پاکستان ميں 1 کروڑ لوگوں کی مادری زبان ہے مگر اسے بھارت اور پاکستان کے تقریباً 50 کروڑ لوگ بول اور سمجھ سکتے ھیں ۔ جن میں سے تقریباً 10.5 کروڑ لوگ اسے باقاعدہ بولتے ھیں۔" "\n"
                "" "\n"
                "بايثون" "\n"
                "=====" "\n"
                "" "\n"
                "**بايثون** لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (OOP) وقابلة للتطوير بالإضافة إلى أنها مجانية و مفتوحة المصدر. صُنفت بالأساس كلغة تفسيرية ، بايثون مصممة أصلاً للأداء بعض المهام الخاصة أو المحدودة. إلا أنه يمكن استخدامها بايثون لإنجاز المشاريع الضخمه كأي لغة برمجية أخرى،  غالباً ما يُنصح المبتدئين في ميدان البرمجة بتعلم هذه اللغة لأنها من بين أسهل اللغات البرمجية تعلماً." "\n"
                "" "\n"
                "|||||||||||||||||||||||||||||THIS SHOULD BE RTL|||||||||||||||||||||||||" "\n"
                "" "\n"
                R"((نشأت بايثون في مركز CWI (مركز العلوم والحاسب الآلي) بأمستردام على يد جويدو فان رُزوم. تم تطويرها بلغة C. أطلق فان رُزوم اسم "بايثون" على لغته تعبيرًا عن إعجابه بفِرقَة مسرحية هزلية شهيرة من بريطانيا، كانت تطلق على نفسها اسم مونتي بايثون Monty Python.)" "\n"
                "" "\n"
                "تتميز بايثون بمجتمعها النشط ، كما أن لها الكثير من المكتبات البرمجية ذات الأغراض الخاصة والتي برمجها أشخاص من مجتمع هذه اللغة ، مثلاً مكتبة PyGame التي توفر مجموعه من الوظائف من اجل برمجة الالعاب. ويمكن لبايثون التعامل مع العديد من أنواع قواعد البيانات مثل MySQL وغيره." "\n"
                "" "\n"
                "##أمثلة " "\n"
                "مثال Hello World!" "\n"
                "" "\n"
                R"(    print "Hello World!")" "\n"
                "" "\n"
                "" "\n"
                "مثال لاستخراج المضروب Factorial :" "\n"
                "" "\n"
                "    num = 1" "\n"
                "    x = raw_input('Insert the number please ')" "\n"
                "    x = int(x)" "\n"
                " " "\n"
                "    if x > 69:" "\n"
                "     print 'Math Error !'" "\n"
                "    else:" "\n"
                "     while x > 1:" "\n"
                "      num *= x" "\n"
                "      x = x-1" "\n"
                " " "\n"
                "     print num" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "##وصلات خارجية " "\n"
                "* [الموقع الرسمي للغة بايثون](http://www.python.org)" "\n"
                "" "\n"
                " بذرة حاس " "\n"
                "" "\n"
                "" "\n"
                "**Недвард «Нед» Фландерс** (Nedward «Ned» Flanders) — вымышленный персонаж мультсериала «[Симпсоны][]», озвученный Гарри Ширером. Он и его семья живут по соседству от семьи Симпсонов. Набожный христианин, Нед является одним из столпов морали Спрингфилда. В эпизоде «Alone Again, Natura-Diddily»  он овдовел, его жена Мод погибла в результате несчастного случая. " "\n"
                "" "\n"
                "Нед был одним из первых персонажей в мультсериале, который не был членом семьи Симпсонов. Начиная с первых серий, он регулярно появляется в «Симпсонах». Считается, что Нед Фландерс был назван в честь улицы *Northeast Flanders St.* в [Портленде](http://www.portland.gov), Орегон, родном городе создателя мультсериала Мэтта Грейнинга]]. Надпись на указателе улицы *NE Flanders St.* хулиганы часто исправляли на _NED Flanders St._" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><strong>Python</strong>（パイソン）は、<a href="http://en.wikipedia.org/wiki/Guido_van_Rossum">Guido van Rossum</a> によって作られたオープンソースのオブジェクト指向スクリプト言語。<a href="http://ja.wikipedia.org/wiki/Perl">Perl</a>とともに欧米で広く普及している。イギリスのテレビ局 BBC が製作したコメディ番組『空飛ぶモンティ・パイソン』にちなんで名付けられた。 (Pythonには、爬虫類のニシキヘビの意味があり、Python言語のマスコットやアイコンとして使われることがある。)</p>)" "\n"
                     "<p>|||||||||||||||||||||||||||||THIS SHOULD BE LTR|||||||||||||||||||||||||</p>" "\n"
                     R"(<p dir="rtl">|||||||||||||||||||||||||||||THIS SHOULD BE RTL|||||||||||||||||||||||||  </p>)" "\n"
                     R"(<p dir="ltr">(<strong>بايثون</strong> لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (THIS SHOULD BE LTR ) وقابلة للتطوير    بالإضافة إلى أنها مجانية و مفتوح </p>)" "\n"
                     "<p>پایتون زبان برنامه‌نویسی تفسیری و سطح بالا ، شی‌گرا و یک زبان برنامه‌نویسی تفسیری سمت سرور قدرتمند است که توسط گیدو ون روسوم در سال ۱۹۹۰ ساخته شد. این زبان در ویژگی‌ها شبیه پرل، روبی، اسکیم، اسمال‌تاک و تی‌سی‌ال است و از مدیریت خودکار حافظه استفاده می‌کند</p>" "\n"
                     "<p>Python，是一种面向对象的、直譯式的计算机程序设计语言，也是一种功能强大而完善的通用型语言，已经具有十多年的发展历史，成熟且稳定。</p>" "\n"
                     "<p>ބްލޫ ވޭލްގެ ދޫ މަތީގައި އެއްފަހަރާ 50 މީހުންނަށް ތިބެވިދާނެވެ. ބޮޑު މަހުގެ ދުލަކީ އެހާމެ ބޮޑު އެއްޗެކެވެ.</p>" "\n"
                     R"(<p><strong>உருது</strong> 13ஆம் நூற்றாண்டில் உருவான ஒரு இந்தோ-ஐரோப்பிய மொழியாகும். உருது, ஹிந்தியுடன் சேர்த்து "ஹிந்துஸ்தானி" என அழைக்கப்படுகின்றது. மண்டரின், ஆங்கிலம் ஆகியவற்றுக்கு அடுத்தபடியாக மூன்றாவது கூடிய அளவு மக்களால் புரிந்து கொள்ளப்படக்கூடியது ஹிந்துஸ்தானியேயாகும். தாய் மொழியாகப் பேசுபவர்கள் எண்ணிக்கையின் அடிப்படையில் உருது உலகின் 20 ஆவது பெரிய மொழியாகும். 6 கோடி மக்கள் இதனைத் தாய் மொழியாகக் கொண்டுள்ளார்கள். இரண்டாவது மொழியாகக் கொண்டுள்ளவர்கள் உட்பட 11 கோடிப் பேர் இதனைப் பேசுகிறார்கள். உருது பாகிஸ்தானின் அரசகரும மொழியாகவும், இந்தியாவின் அரசகரும மொழிகளுள் ஒன்றாகவும் விளங்குகிறது.</p>)" "\n"
                     "<p>اردو ہندوآریائی زبانوں کی ہندويورپی شاخ کی ایک زبان ہے جو تيرھويں صدی ميں بر صغير ميں پيدا ہوئی ـ اردو پاکستان کی سرکاری زبان ہے اور بھارت کی سرکاری زبانوں ميں سے ايک ہے۔ اردو بھارت ميں 5 کروڑ اور پاکستان ميں 1 کروڑ لوگوں کی مادری زبان ہے مگر اسے بھارت اور پاکستان کے تقریباً 50 کروڑ لوگ بول اور سمجھ سکتے ھیں ۔ جن میں سے تقریباً 10.5 کروڑ لوگ اسے باقاعدہ بولتے ھیں۔</p>" "\n"
                     "<h1>بايثون</h1>" "\n"
                     "<p><strong>بايثون</strong> لغة برمجة حديثة بسيطة، واضحة، سريعة ، تستخدم أسلوب البرمجة الكائنية (OOP) وقابلة للتطوير بالإضافة إلى أنها مجانية و مفتوحة المصدر. صُنفت بالأساس كلغة تفسيرية ، بايثون مصممة أصلاً للأداء بعض المهام الخاصة أو المحدودة. إلا أنه يمكن استخدامها بايثون لإنجاز المشاريع الضخمه كأي لغة برمجية أخرى،  غالباً ما يُنصح المبتدئين في ميدان البرمجة بتعلم هذه اللغة لأنها من بين أسهل اللغات البرمجية تعلماً.</p>" "\n"
                     "<p>|||||||||||||||||||||||||||||THIS SHOULD BE RTL|||||||||||||||||||||||||</p>" "\n"
                     R"(<p>(نشأت بايثون في مركز CWI (مركز العلوم والحاسب الآلي) بأمستردام على يد جويدو فان رُزوم. تم تطويرها بلغة C. أطلق فان رُزوم اسم "بايثون" على لغته تعبيرًا عن إعجابه بفِرقَة مسرحية هزلية شهيرة من بريطانيا، كانت تطلق على نفسها اسم مونتي بايثون Monty Python.</p>)" "\n"
                     "<p>تتميز بايثون بمجتمعها النشط ، كما أن لها الكثير من المكتبات البرمجية ذات الأغراض الخاصة والتي برمجها أشخاص من مجتمع هذه اللغة ، مثلاً مكتبة PyGame التي توفر مجموعه من الوظائف من اجل برمجة الالعاب. ويمكن لبايثون التعامل مع العديد من أنواع قواعد البيانات مثل MySQL وغيره.</p>" "\n"
                     "<h2>أمثلة</h2>" "\n"
                     "<p>مثال Hello World!</p>" "\n"
                     R"(<pre><code>print "Hello World!")" "\n"
                     "</code></pre>" "\n"
                     "<p>مثال لاستخراج المضروب Factorial :</p>" "\n"
                     "<pre><code>num = 1" "\n"
                     "x = raw_input('Insert the number please ')" "\n"
                     "x = int(x)" "\n"
                     "" "\n"
                     "if x &gt; 69:" "\n"
                     " print 'Math Error !'" "\n"
                     "else:" "\n"
                     " while x &gt; 1:" "\n"
                     "  num *= x" "\n"
                     "  x = x-1" "\n"
                     "" "\n"
                     " print num" "\n"
                     "</code></pre>" "\n"
                     "<h2>وصلات خارجية</h2>" "\n"
                     "<ul>" "\n"
                     R"(<li><a href="http://www.python.org">الموقع الرسمي للغة بايثون</a></li>)" "\n"
                     "</ul>" "\n"
                     "<p>بذرة حاس </p>" "\n"
                     "<p><strong>Недвард «Нед» Фландерс</strong> (Nedward «Ned» Flanders) — вымышленный персонаж мультсериала «[Симпсоны][]», озвученный Гарри Ширером. Он и его семья живут по соседству от семьи Симпсонов. Набожный христианин, Нед является одним из столпов морали Спрингфилда. В эпизоде «Alone Again, Natura-Diddily»  он овдовел, его жена Мод погибла в результате несчастного случая. </p>" "\n"
                     R"(<p>Нед был одним из первых персонажей в мультсериале, который не был членом семьи Симпсонов. Начиная с первых серий, он регулярно появляется в «Симпсонах». Считается, что Нед Фландерс был назван в честь улицы <em>Northeast Flanders St.</em> в <a href="http://www.portland.gov">Портленде</a>, Орегон, родном городе создателя мультсериала Мэтта Грейнинга]]. Надпись на указателе улицы <em>NE Flanders St.</em> хулиганы часто исправляли на <em>NED Flanders St.</em></p>)"));
}

void TestMISC::blank_block_quote()
{
    QString converted = this->md->convert(
                "" "\n"
                "aaaaaaaaaaa" "\n"
                "" "\n"
                "> " "\n"
                "" "\n"
                "bbbbbbbbbbb" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>aaaaaaaaaaa</p>" "\n"
                     "<blockquote></blockquote>" "\n"
                     "<p>bbbbbbbbbbb</p>"));
}

void TestMISC::blank_lines_in_codeblocks()
{
    QString converted = this->md->convert(
                "Preserve blank lines in code blocks with tabs:" "\n"
                "" "\n"
                "    a code block" "\n"
                "    " "\n"
                "    two tabbed lines" "\n"
                "    " "\n"
                "    " "\n"
                "    three tabbed lines" "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    four tabbed lines" "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    five tabbed lines" "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    six tabbed lines" "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    End of tabbed block" "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "    " "\n"
                "And without tabs:" "\n"
                "" "\n"
                "    a code block" "\n"
                "" "\n"
                "    two blank lines" "\n"
                "" "\n"
                "" "\n"
                "    three blank lines" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "    four blank lines" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "    five blank lines" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "    six blank lines" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "    End of block" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "End of document");
    QCOMPARE(converted,
             QString("<p>Preserve blank lines in code blocks with tabs:</p>" "\n"
                     "<pre><code>a code block" "\n"
                     "" "\n"
                     "two tabbed lines" "\n"
                     "" "\n"
                     "" "\n"
                     "three tabbed lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "four tabbed lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "five tabbed lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "six tabbed lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "End of tabbed block" "\n"
                     "</code></pre>" "\n"
                     "<p>And without tabs:</p>" "\n"
                     "<pre><code>a code block" "\n"
                     "" "\n"
                     "two blank lines" "\n"
                     "" "\n"
                     "" "\n"
                     "three blank lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "four blank lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "five blank lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "six blank lines" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "" "\n"
                     "End of block" "\n"
                     "</code></pre>" "\n"
                     "<p>End of document</p>"));
}

void TestMISC::block_html5()
{
    QString converted = this->md->convert(
                "<section>" "\n"
                "    <header>" "\n"
                "        <hgroup>" "\n"
                "            <h1>Hello :-)</h1>" "\n"
                "        </hgroup>" "\n"
                "    </header>" "\n"
                "    <figure>" "\n"
                R"(        <img src="image.png" alt="" />)" "\n"
                "        <figcaption>Caption</figcaption>" "\n"
                "    </figure>" "\n"
                "    <footer>" "\n"
                "        <p>Some footer</p>" "\n"
                "    </footer>" "\n"
                "</section><figure></figure>" "\n"
                "");
    QCOMPARE(converted,
             QString("<section>" "\n"
                     "    <header>" "\n"
                     "        <hgroup>" "\n"
                     "            <h1>Hello :-)</h1>" "\n"
                     "        </hgroup>" "\n"
                     "    </header>" "\n"
                     "    <figure>" "\n"
                     R"(        <img src="image.png" alt="" />)" "\n"
                     "        <figcaption>Caption</figcaption>" "\n"
                     "    </figure>" "\n"
                     "    <footer>" "\n"
                     "        <p>Some footer</p>" "\n"
                     "    </footer>" "\n"
                     "</section>" "\n"
                     "" "\n"
                     "<figure></figure>"));
}

void TestMISC::block_html_attr()
{
    QString converted = this->md->convert(
                "<blockquote>" "\n"
                "Raw HTML processing should not confuse this with the blockquote below" "\n"
                "</blockquote>" "\n"
                R"(<div id="current-content">)" "\n"
                R"(    <div id="primarycontent" class="hfeed">)" "\n"
                R"(        <div id="post-">)" "\n"
                R"(            <div class="page-head">)" "\n"
                "                <h2>Header2</h2>" "\n"
                "            </div>" "\n"
                R"(            <div class="entry-content">)" "\n"
                "                <h3>Header3</h3>" "\n"
                "                    <p>Paragraph</p>" "\n"
                "                <h3>Header3</h3>" "\n"
                "                    <p>Paragraph</p>" "\n"
                "                    <blockquote>" "\n"
                "                        <p>Paragraph</p>" "\n"
                "                    </blockquote>" "\n"
                "                    <p>Paragraph</p>" "\n"
                R"(                    <p><a href="/somelink">linktext</a></p>)" "\n"
                "            </div>" "\n"
                "        </div><!-- #post-ID -->" "\n"
                "        <!-- add contact form here -->" "\n"
                "    </div><!-- #primarycontent -->" "\n"
                "</div><!-- #current-content -->" "\n"
                "");
    QCOMPARE(converted,
             QString("<blockquote>" "\n"
                     "Raw HTML processing should not confuse this with the blockquote below" "\n"
                     "</blockquote>" "\n"
                     "" "\n"
                     R"(<div id="current-content">)" "\n"
                     R"(    <div id="primarycontent" class="hfeed">)" "\n"
                     R"(        <div id="post-">)" "\n"
                     R"(            <div class="page-head">)" "\n"
                     "                <h2>Header2</h2>" "\n"
                     "            </div>" "\n"
                     R"(            <div class="entry-content">)" "\n"
                     "                <h3>Header3</h3>" "\n"
                     "                    <p>Paragraph</p>" "\n"
                     "                <h3>Header3</h3>" "\n"
                     "                    <p>Paragraph</p>" "\n"
                     "                    <blockquote>" "\n"
                     "                        <p>Paragraph</p>" "\n"
                     "                    </blockquote>" "\n"
                     "                    <p>Paragraph</p>" "\n"
                     R"(                    <p><a href="/somelink">linktext</a></p>)" "\n"
                     "            </div>" "\n"
                     "        </div><!-- #post-ID -->" "\n"
                     "        <!-- add contact form here -->" "\n"
                     "    </div><!-- #primarycontent -->" "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<!-- #current-content -->"));
}

void TestMISC::block_html_simple()
{
    QString converted = this->md->convert(
                "<p>foo</p>" "\n"
                "<ul>" "\n"
                "<li>" "\n"
                "<p>bar</p>" "\n"
                "</li>" "\n"
                "<li>" "\n"
                "<p>baz</p>" "\n"
                "</li>" "\n"
                "</ul>" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>foo</p>" "\n"
                     "" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>bar</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>baz</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::blockquote()
{
    QString converted = this->md->convert(
                "> blockquote with no whitespace before `>`." "\n"
                "" "\n"
                "foo" "\n"
                "" "\n"
                " > blockquote with one space before the `>`." "\n"
                "" "\n"
                "bar" "\n"
                "" "\n"
                "  > blockquote with 2 spaces." "\n"
                "" "\n"
                "baz" "\n"
                "" "\n"
                "   > this has three spaces so its a paragraph." "\n"
                "" "\n"
                "blah" "\n"
                "" "\n"
                "    > this one had four so it's a code block." "\n"
                "" "\n"
                ">   > this nested blockquote has 0 on level one and 3 (one after the first `>` + 2 more) on level 2." "\n"
                "" "\n"
                ">    > and this has 4 on level 2 - another code block." "\n"
                "");
    QCOMPARE(converted,
             QString("<blockquote>" "\n"
                     "<p>blockquote with no whitespace before <code>&gt;</code>.</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>foo</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>blockquote with one space before the <code>&gt;</code>.</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>bar</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>blockquote with 2 spaces.</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>baz</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>this has three spaces so its a paragraph.</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>blah</p>" "\n"
                     "<pre><code>&gt; this one had four so it's a code block." "\n"
                     "</code></pre>" "\n"
                     "<blockquote>" "\n"
                     "<blockquote>" "\n"
                     "<p>this nested blockquote has 0 on level one and 3 (one after the first <code>&gt;</code> + 2 more) on level 2.</p>" "\n"
                     "<p>and this has 4 on level 2 - another code block.</p>" "\n"
                     "</blockquote>" "\n"
                     "</blockquote>"));
}

void TestMISC::blockquote_below_paragraph()
{
    QString converted = this->md->convert(
                "Paragraph" "\n"
                "> Block quote" "\n"
                "> Yep" "\n"
                "" "\n"
                "Paragraph" "\n"
                ">no space" "\n"
                ">Nope" "\n"
                "" "\n"
                "Paragraph one" "\n"
                "> blockquote" "\n"
                "More blockquote." "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Paragraph</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>Block quote" "\n"
                     "Yep</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>Paragraph</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>no space" "\n"
                     "Nope</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>Paragraph one</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>blockquote" "\n"
                     "More blockquote.</p>" "\n"
                     "</blockquote>"));
}

void TestMISC::blockquote_hr()
{
    QString converted = this->md->convert(
                "This is a paragraph." "\n"
                "" "\n"
                "---" "\n"
                "" "\n"
                "> Block quote with horizontal lines." "\n"
                "" "\n"
                "> ---" "\n"
                "" "\n"
                "> > Double block quote." "\n"
                "" "\n"
                "> > ---" "\n"
                "" "\n"
                "> > End of the double block quote." "\n"
                "" "\n"
                "> A new paragraph." "\n"
                "> With multiple lines." "\n"
                "Even a lazy line." "\n"
                "" "\n"
                "> ---" "\n"
                "" "\n"
                "> The last line." "\n"
                "");
    QCOMPARE(converted,
             QString("<p>This is a paragraph.</p>" "\n"
                     "<hr />" "\n"
                     "<blockquote>" "\n"
                     "<p>Block quote with horizontal lines.</p>" "\n"
                     "<hr />" "\n"
                     "<blockquote>" "\n"
                     "<p>Double block quote.</p>" "\n"
                     "<hr />" "\n"
                     "<p>End of the double block quote.</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>A new paragraph." "\n"
                     "With multiple lines." "\n"
                     "Even a lazy line.</p>" "\n"
                     "<hr />" "\n"
                     "<p>The last line.</p>" "\n"
                     "</blockquote>"));
}

void TestMISC::bold_links()
{
    QString converted = this->md->convert(
                "**bold [link](http://example.com)**" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><strong>bold <a href="http://example.com">link</a></strong></p>)"));
}

void TestMISC::br()
{
    QString converted = this->md->convert(
                "Output:" "\n"
                "" "\n"
                "    <p>Some of these words <em>are emphasized</em>." "\n"
                "    Some of these words <em>are emphasized also</em>.</p>" "\n"
                "" "\n"
                "    <p>Use two asterisks for <strong>strong emphasis</strong>." "\n"
                "    Or, if you prefer, <strong>use two underscores instead</strong>.</p>" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "## Lists ##" "\n"
                "" "\n"
                "Unordered (bulleted) lists use asterisks, pluses, and hyphens (`*`," "\n"
                "`+`, and `-`) as list markers. These three markers are" "\n"
                "interchangable; this:" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Output:</p>" "\n"
                     "<pre><code>&lt;p&gt;Some of these words &lt;em&gt;are emphasized&lt;/em&gt;." "\n"
                     "Some of these words &lt;em&gt;are emphasized also&lt;/em&gt;.&lt;/p&gt;" "\n"
                     "" "\n"
                     "&lt;p&gt;Use two asterisks for &lt;strong&gt;strong emphasis&lt;/strong&gt;." "\n"
                     "Or, if you prefer, &lt;strong&gt;use two underscores instead&lt;/strong&gt;.&lt;/p&gt;" "\n"
                     "</code></pre>" "\n"
                     "<h2>Lists</h2>" "\n"
                     "<p>Unordered (bulleted) lists use asterisks, pluses, and hyphens (<code>*</code>," "\n"
                     "<code>+</code>, and <code>-</code>) as list markers. These three markers are" "\n"
                     "interchangable; this:</p>"));
}

void TestMISC::bracket_re()
{
    QString converted = this->md->convert(
                "" "\n"
                "[x" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>[x" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx" "\n"
                     "xxx xxx xxx xxx xxx xxx xxx xxx</p>"));
}

void TestMISC::brackets_in_img_title()
{
    QString converted = this->md->convert(
                "![alt](local-img.jpg)" "\n"
                R"(![alt](local-img.jpg ""))" "\n"
                R"(![alt](local-img.jpg "normal title"))" "\n"
                "" "\n"
                "![alt](local-img.jpg \"(just title in brackets)\")" "\n"
                "![alt](local-img.jpg \"title with brackets (I think)\")" "\n"
                "" "\n"
                R"(![alt](local-img.jpg "("))" "\n"
                R"(![alt](local-img.jpg "(open only"))" "\n"
                "![alt](local-img.jpg \")\")" "\n"
                "![alt](local-img.jpg \"close only)\")" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><img alt="alt" src="local-img.jpg" />)" "\n"
                     R"(<img alt="alt" src="local-img.jpg" title="" />)" "\n"
                     R"(<img alt="alt" src="local-img.jpg" title="normal title" /></p>)" "\n"
                     "<p><img alt=\"alt\" src=\"local-img.jpg\" title=\"(just title in brackets)\" />" "\n"
                     "<img alt=\"alt\" src=\"local-img.jpg\" title=\"title with brackets (I think)\" /></p>" "\n"
                     R"(<p><img alt="alt" src="local-img.jpg" title="(" />)" "\n"
                     R"(<img alt="alt" src="local-img.jpg" title="(open only" />)" "\n"
                     "<img alt=\"alt\" src=\"local-img.jpg\" title=\")\" />" "\n"
                     "<img alt=\"alt\" src=\"local-img.jpg\" title=\"close only)\" /></p>"));
}

void TestMISC::code_first_line()
{
    QString converted = this->md->convert(
                R"(    print "This is a code block.")" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<pre><code>print "This is a code block.")" "\n"
                     "</code></pre>"));
}

void TestMISC::comments()
{
    QString converted = this->md->convert(
                "X<0" "\n"
                "" "\n"
                "X>0" "\n"
                "" "\n"
                "<!-- A comment -->" "\n"
                "" "\n"
                "<div>as if</div>" "\n"
                "" "\n"
                "<!-- comment -->" "\n"
                "__no blank line__" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>X&lt;0</p>" "\n"
                     "<p>X&gt;0</p>" "\n"
                     "<!-- A comment -->" "\n"
                     "" "\n"
                     "<div>as if</div>" "\n"
                     "" "\n"
                     "<!-- comment -->" "\n"
                     "" "\n"
                     "<p><strong>no blank line</strong></p>"));
}

void TestMISC::div()
{
    QString converted = this->md->convert(
                R"(<div id="sidebar">)" "\n"
                "" "\n"
                "   _foo_" "\n"
                "" "\n"
                "</div>" "\n"
                "" "\n"
                "And now in uppercase:" "\n"
                "" "\n"
                "<DIV>" "\n"
                "foo" "\n"
                "</DIV>" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<div id="sidebar">)" "\n"
                     "" "\n"
                     "   _foo_" "\n"
                     "" "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<p>And now in uppercase:</p>" "\n"
                     "<DIV>" "\n"
                     "foo" "\n"
                     "</DIV>"));
}

void TestMISC::em_around_links()
{
    QString converted = this->md->convert(
                "# Title" "\n"
                "" "\n"
                "  - *[Python in Markdown](https://pythonhosted.org/Markdown/) by some" "\n"
                "    great folks* - This *does* work as expected." "\n"
                "  - _[Python in Markdown](https://pythonhosted.org/Markdown/) by some" "\n"
                "    great folks_ - This *does* work as expected." "\n"
                "  - [_Python in Markdown_](https://pythonhosted.org/Markdown/) by some" "\n"
                "    great folks - This *does* work as expected." "\n"
                "  - [_Python in Markdown_](https://pythonhosted.org/Markdown/) _by some" "\n"
                "    great folks_ - This *does* work as expected." "\n"
                "" "\n"
                "_[Python in Markdown](https://pythonhosted.org/Markdown/) by some" "\n"
                "great folks_ - This *does* work as expected." "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>Title</h1>" "\n"
                     "<ul>" "\n"
                     R"(<li><em><a href="https://pythonhosted.org/Markdown/">Python in Markdown</a> by some)" "\n"
                     "    great folks</em> - This <em>does</em> work as expected.</li>" "\n"
                     R"(<li><em><a href="https://pythonhosted.org/Markdown/">Python in Markdown</a> by some)" "\n"
                     "    great folks</em> - This <em>does</em> work as expected.</li>" "\n"
                     R"(<li><a href="https://pythonhosted.org/Markdown/"><em>Python in Markdown</em></a> by some)" "\n"
                     "    great folks - This <em>does</em> work as expected.</li>" "\n"
                     R"(<li><a href="https://pythonhosted.org/Markdown/"><em>Python in Markdown</em></a> <em>by some)" "\n"
                     "    great folks</em> - This <em>does</em> work as expected.</li>" "\n"
                     "</ul>" "\n"
                     R"(<p><em><a href="https://pythonhosted.org/Markdown/">Python in Markdown</a> by some)" "\n"
                     "great folks</em> - This <em>does</em> work as expected.</p>"));
}

void TestMISC::em_strong()
{
    QString converted = this->md->convert(
                "One asterisk: *" "\n"
                "" "\n"
                "One underscore: _" "\n"
                "" "\n"
                "Two asterisks: **" "\n"
                "" "\n"
                "With spaces: * *" "\n"
                "" "\n"
                "Two underscores __" "\n"
                "" "\n"
                "with spaces: _ _" "\n"
                "" "\n"
                "three asterisks: ***" "\n"
                "" "\n"
                "with spaces: * * *" "\n"
                "" "\n"
                "three underscores: ___" "\n"
                "" "\n"
                "with spaces: _ _ _" "\n"
                "" "\n"
                "One char: _a_" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>One asterisk: *</p>" "\n"
                     "<p>One underscore: _</p>" "\n"
                     "<p>Two asterisks: **</p>" "\n"
                     "<p>With spaces: * *</p>" "\n"
                     "<p>Two underscores __</p>" "\n"
                     "<p>with spaces: _ _</p>" "\n"
                     "<p>three asterisks: ***</p>" "\n"
                     "<p>with spaces: * * *</p>" "\n"
                     "<p>three underscores: ___</p>" "\n"
                     "<p>with spaces: _ _ _</p>" "\n"
                     "<p>One char: <em>a</em></p>"));
}

void TestMISC::em_strong_complex()
{
    QString converted = this->md->convert(
                "___test test__ test test_" "\n"
                "" "\n"
                "___test test_ test test__" "\n"
                "" "\n"
                "___test___" "\n"
                "" "\n"
                "__test___" "\n"
                "" "\n"
                "___test_ test___" "\n"
                "" "\n"
                "___test_ test__" "\n"
                "" "\n"
                "_test_test test_test_" "\n"
                "" "\n"
                "***test test** test test*" "\n"
                "" "\n"
                "***test test* test test**" "\n"
                "" "\n"
                "**test*" "\n"
                "" "\n"
                "***test***" "\n"
                "" "\n"
                "**test***" "\n"
                "" "\n"
                "***test* test**" "\n"
                "" "\n"
                "*test*test test*test*");
    QCOMPARE(converted,
             QString("<p><em><strong>test test</strong> test test</em></p>" "\n"
                     "<p><strong><em>test test</em> test test</strong></p>" "\n"
                     "<p><strong><em>test</em></strong></p>" "\n"
                     "<p><strong>test</strong>_</p>" "\n"
                     "<p><strong><em>test</em> test</strong>_</p>" "\n"
                     "<p><strong><em>test</em> test</strong></p>" "\n"
                     "<p><em>test_test test_test</em></p>" "\n"
                     "<p><em><strong>test test</strong> test test</em></p>" "\n"
                     "<p><strong><em>test test</em> test test</strong></p>" "\n"
                     "<p>*<em>test</em></p>" "\n"
                     "<p><strong><em>test</em></strong></p>" "\n"
                     "<p><strong>test</strong>*</p>" "\n"
                     "<p><strong><em>test</em> test</strong></p>" "\n"
                     "<p><em>test</em>test test<em>test</em></p>"));
}

void TestMISC::email()
{
    QString converted = this->md->convert(
                "" "\n"
                "asdfasdfadsfasd <yuri@freewisdom.org> or you can say " "\n"
                "instead <mailto:yuri@freewisdom.org>" "\n"
                "" "\n"
                "<bob&sue@example.com>" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p>asdfasdfadsfasd <a href="&#109;&#97;&#105;&#108;&#116;&#111;&#58;&#121;&#117;&#114;&#105;&#64;&#102;&#114;&#101;&#101;&#119;&#105;&#115;&#100;&#111;&#109;&#46;&#111;&#114;&#103;">&#121;&#117;&#114;&#105;&#64;&#102;&#114;&#101;&#101;&#119;&#105;&#115;&#100;&#111;&#109;&#46;&#111;&#114;&#103;</a> or you can say )" "\n"
                     R"(instead <a href="&#109;&#97;&#105;&#108;&#116;&#111;&#58;&#121;&#117;&#114;&#105;&#64;&#102;&#114;&#101;&#101;&#119;&#105;&#115;&#100;&#111;&#109;&#46;&#111;&#114;&#103;">&#121;&#117;&#114;&#105;&#64;&#102;&#114;&#101;&#101;&#119;&#105;&#115;&#100;&#111;&#109;&#46;&#111;&#114;&#103;</a></p>)" "\n"
                     R"(<p><a href="&#109;&#97;&#105;&#108;&#116;&#111;&#58;&#98;&#111;&#98;&#38;&#115;&#117;&#101;&#64;&#101;&#120;&#97;&#109;&#112;&#108;&#101;&#46;&#99;&#111;&#109;">&#98;&#111;&#98;&amp;&#115;&#117;&#101;&#64;&#101;&#120;&#97;&#109;&#112;&#108;&#101;&#46;&#99;&#111;&#109;</a></p>)"));
}

void TestMISC::escaped_chars_in_js()
{
    QString converted = this->md->convert(
                R"(<span id="e116142240">[javascript protected email address]</span>)" "\n"
                R"(<script type="text/javascript">)" "\n"
                R"(    var a="gqMjyw7lZCaKk6p0J3uAUYS1.dbIW2hXzDHmiVNotOPRe_Ev@c4Gs58+LBr-F9QTfxn";)" "\n"
                R"(    var b=a.split("").sort().join("");)" "\n"
                R"(    var c="F_-F6F_-FMe_";)" "\n"
                R"(    var d="";)" "\n"
                "    for(var e=0;e<c.length;e++)" "\n"
                "    d+=b.charAt(a.indexOf(c.charAt(e)));" "\n"
                "        document" "\n"
                R"(            .getElementById("e116142240"))" "\n"
                R"(            .innerHTML="<a href=\"mailto:"+d+"\">"+d+"</a>";)" "\n"
                "</script>" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><span id="e116142240">[javascript protected email address]</span>)" "\n"
                     R"(<script type="text/javascript">)" "\n"
                     R"(    var a="gqMjyw7lZCaKk6p0J3uAUYS1.dbIW2hXzDHmiVNotOPRe_Ev@c4Gs58+LBr-F9QTfxn";)" "\n"
                     R"(    var b=a.split("").sort().join("");)" "\n"
                     R"(    var c="F_-F6F_-FMe_";)" "\n"
                     R"(    var d="";)" "\n"
                     "    for(var e=0;e<c.length;e++)" "\n"
                     "    d+=b.charAt(a.indexOf(c.charAt(e)));" "\n"
                     "        document" "\n"
                     R"(            .getElementById("e116142240"))" "\n"
                     R"(            .innerHTML="<a href=\"mailto:"+d+"\">"+d+"</a>";)" "\n"
                     "</script></p>"));
}

void TestMISC::escaped_links()
{
    QString converted = this->md->convert(
                "Backslashed in links:" "\n"
                "" "\n"
                R"([q=go:GO\\:0000307](/query?q=go:GO\\:0000307))" "\n"
                "" "\n"
                R"([q=go:GO\\:0000308][foo])" "\n"
                "" "\n"
                R"([foo]: /query?q=go:GO\:0000308 "/query?q=go:GO\:0000308")" "\n"
                "" "\n"
                R"(a \non-escaped char.)");
    QCOMPARE(converted,
             QString("<p>Backslashed in links:</p>" "\n"
                     R"(<p><a href="/query?q=go:GO\:0000307">q=go:GO\:0000307</a></p>)" "\n"
                     R"(<p><a href="/query?q=go:GO\:0000308" title="/query?q=go:GO\:0000308">q=go:GO\:0000308</a></p>)" "\n"
                     R"(<p>a \non-escaped char.</p>)"));
}

void TestMISC::funky_list()
{
    QString converted = this->md->convert(
                "1. this starts a list *with* numbers" "\n"
                R"(+  this will show as number "2")" "\n"
                R"(*  this will show as number "3.")" "\n"
                "9. any number, +, -, or * will keep the list going." "\n"
                "" "\n"
                "aaaaaaaaaaaaaaa" "\n"
                "" "\n"
                "- now a normal list" "\n"
                "- and more" "\n"
                "");
    QCOMPARE(converted,
             QString("<ol>" "\n"
                     "<li>this starts a list <em>with</em> numbers</li>" "\n"
                     R"(<li>this will show as number "2"</li>)" "\n"
                     R"(<li>this will show as number "3."</li>)" "\n"
                     "<li>any number, +, -, or * will keep the list going.</li>" "\n"
                     "</ol>" "\n"
                     "<p>aaaaaaaaaaaaaaa</p>" "\n"
                     "<ul>" "\n"
                     "<li>now a normal list</li>" "\n"
                     "<li>and more</li>" "\n"
                     "</ul>"));
}

void TestMISC::h1()
{
    QString converted = this->md->convert(
                "Header" "\n"
                "------" "\n"
                "" "\n"
                "Header 2" "\n"
                "========" "\n"
                "" "\n"
                "### H3" "\n"
                "" "\n"
                "H1" "\n"
                "= " "\n"
                "" "\n"
                "H2" "\n"
                "--" "\n"
                "");
    QCOMPARE(converted,
             QString("<h2>Header</h2>" "\n"
                     "<h1>Header 2</h1>" "\n"
                     "<h3>H3</h3>" "\n"
                     "<h1>H1</h1>" "\n"
                     "<h2>H2</h2>"));
}

void TestMISC::hash()
{
    QString converted = this->md->convert(
                "a" "\n"
                "" "\n"
                "<pre>" "\n"
                "#!/usr/bin/python" "\n"
                "hello</pre>" "\n"
                "" "\n"
                "a" "\n"
                "" "\n"
                "<pre>" "\n"
                "!/usr/bin/python" "\n"
                "hello</pre>" "\n"
                "" "\n"
                "a" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>a</p>" "\n"
                     "<pre>" "\n"
                     "#!/usr/bin/python" "\n"
                     "hello</pre>" "\n"
                     "" "\n"
                     "<p>a</p>" "\n"
                     "<pre>" "\n"
                     "!/usr/bin/python" "\n"
                     "hello</pre>" "\n"
                     "" "\n"
                     "<p>a</p>"));
}

void TestMISC::header_in_lists()
{
    QString converted = this->md->convert(
                "Tight List:" "\n"
                "" "\n"
                "* #Header1" "\n"
                "Line 1-2 - **not** a header *or* paragraph!" "\n"
                "* #Header2" "\n"
                "Line 2-2 - not a header or paragraph!" "\n"
                "" "\n"
                "Loose List:" "\n"
                "" "\n"
                "* #Header1" "\n"
                "Line 1-2 - *a* paragraph" "\n"
                "" "\n"
                "* #Header2" "\n"
                "Line 2-2 - a paragraph" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Tight List:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<h1>Header1</h1>" "\n"
                     "Line 1-2 - <strong>not</strong> a header <em>or</em> paragraph!</li>" "\n"
                     "<li>" "\n"
                     "<h1>Header2</h1>" "\n"
                     "Line 2-2 - not a header or paragraph!</li>" "\n"
                     "</ul>" "\n"
                     "<p>Loose List:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<h1>Header1</h1>" "\n"
                     "<p>Line 1-2 - <em>a</em> paragraph</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<h1>Header2</h1>" "\n"
                     "<p>Line 2-2 - a paragraph</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::headers()
{
    QString converted = this->md->convert(
                "### Hello world" "\n"
                "Line 2" "\n"
                "Line 3" "\n"
                "" "\n"
                "# [Markdown][5]  " "\n"
                "" "\n"
                "# [Markdown](http://some.link.com/)" "\n"
                "" "\n"
                "# [5]: http://foo.com/" "\n"
                "" "\n"
                "# Issue #1: Markdown" "\n"
                "" "\n"
                "Text" "\n"
                "# Header" "\n"
                "Some other text" "\n"
                "");
    QCOMPARE(converted,
             QString("<h3>Hello world</h3>" "\n"
                     "<p>Line 2" "\n"
                     "Line 3</p>" "\n"
                     "<h1>[Markdown][5]</h1>" "\n"
                     R"(<h1><a href="http://some.link.com/">Markdown</a></h1>)" "\n"
                     "<h1>[5]: http://foo.com/</h1>" "\n"
                     "<h1>Issue #1: Markdown</h1>" "\n"
                     "<p>Text</p>" "\n"
                     "<h1>Header</h1>" "\n"
                     "<p>Some other text</p>"));
}

void TestMISC::hline()
{
    QString converted = this->md->convert(
                "" "\n"
                "#Header" "\n"
                "Next line" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>Header</h1>" "\n"
                     "<p>Next line</p>"));
}

void TestMISC::html()
{
    QString converted = this->md->convert(
                "" "\n"
                "<h1>Block level html</h1>" "\n"
                "" "\n"
                "Some inline <b>stuff<b>.  " "\n"
                "" "\n"
                "Now some <arbitrary>arbitrary tags</arbitrary>." "\n"
                "" "\n"
                "<div>More block level html.</div>" "\n"
                "" "\n"
                R"(<div class="foo bar" title="with 'quoted' text." valueless_attr weirdness="<i>foo</i>">)" "\n"
                "Html with various attributes." "\n"
                "</div>" "\n"
                "" "\n"
                "And of course <script>blah</script>." "\n"
                "" "\n"
                "[this <script>link](<script>stuff</script>)" "\n"
                "" "\n"
                R"(Some funky <x\]> inline stuff with markdown escaping syntax.)" "\n"
                "" "\n"
                R"(<img scr="foo.png" title="Only one inline element on a line." />)" "\n"
                "" "\n"
                "And now a line with only an opening bracket:" "\n"
                "" "\n"
                "<" "\n"
                "" "\n"
                "And one with other stuff but no closing bracket:" "\n"
                "" "\n"
                "< foo" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>Block level html</h1>" "\n"
                     "" "\n"
                     "<p>Some inline <b>stuff<b>.  </p>" "\n"
                     "<p>Now some <arbitrary>arbitrary tags</arbitrary>.</p>" "\n"
                     "<div>More block level html.</div>" "\n"
                     "" "\n"
                     R"(<div class="foo bar" title="with 'quoted' text." valueless_attr weirdness="<i>foo</i>">)" "\n"
                     "Html with various attributes." "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<p>And of course <script>blah</script>.</p>" "\n"
                     R"(<p><a href="script&gt;stuff&lt;/script">this <script>link</a></p>)" "\n"
                     R"(<p>Some funky <x\]> inline stuff with markdown escaping syntax.</p>)" "\n"
                     R"(<p><img scr="foo.png" title="Only one inline element on a line." /></p>)" "\n"
                     "<p>And now a line with only an opening bracket:</p>" "\n"
                     "<p>&lt;</p>" "\n"
                     "<p>And one with other stuff but no closing bracket:</p>" "\n"
                     "<p>&lt; foo</p>"));
}

void TestMISC::html_comments()
{
    QString converted = this->md->convert(
                "Here is HTML <!-- **comment** -->" "\n"
                "and once more <p><!--comment--></p>" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Here is HTML <!-- **comment** -->" "\n"
                     "and once more <p><!--comment--></p></p>"));
}

void TestMISC::image()
{
    QString converted = this->md->convert(
                "" "\n"
                R"(![Poster](http://humane_man.jpg "The most humane man."))" "\n"
                "" "\n"
                "![Poster][]" "\n"
                "" "\n"
                R"([Poster]:http://humane_man.jpg "The most humane man.")" "\n"
                "" "\n"
                "![Blank]()");
    QCOMPARE(converted,
             QString(R"(<p><img alt="Poster" src="http://humane_man.jpg" title="The most humane man." /></p>)" "\n"
                     R"(<p><img alt="Poster" src="http://humane_man.jpg" title="The most humane man." /></p>)" "\n"
                     R"(<p><img alt="Blank" src="" /></p>)"));
}

void TestMISC::image_2()
{
    QString converted = this->md->convert(
                "[*link!*](http://src.com/)" "\n"
                "" "\n"
                "*[link](http://www.freewisdom.org)*" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://src.com/"><em>link!</em></a></p>)" "\n"
                     R"(<p><em><a href="http://www.freewisdom.org">link</a></em></p>)"));
}

void TestMISC::image_in_links()
{
    QString converted = this->md->convert(
                "" "\n"
                "" "\n"
                "[![altname](path/to/img_thumb.png)](path/to/image.png)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="path/to/image.png"><img alt="altname" src="path/to/img_thumb.png" /></a></p>)"));
}

void TestMISC::ins_at_start_of_paragraph()
{
    QString converted = this->md->convert(
                "<ins>Hello, fellow developer</ins> this ins should be wrapped in a p." "\n"
                "");
    QCOMPARE(converted,
             QString("<p><ins>Hello, fellow developer</ins> this ins should be wrapped in a p.</p>"));
}

void TestMISC::inside_html()
{
    QString converted = this->md->convert(
                R"(<a href="stuff"> __ok__? </a>)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="stuff"> <strong>ok</strong>? </a></p>)"));
}

void TestMISC::japanese()
{
    QString converted = this->md->convert(
                "パイソン (Python)" "\n"
                "=======" "\n"
                "" "\n"
                "**Python**（パイソン）は、[Guido van Rossum](http://en.wikipedia.org/wiki/Guido_van_Rossum) によって作られたオープンソースのオブジェクト指向スクリプト言語。[Perl](http://ja.wikipedia.org/wiki/Perl)とともに欧米で広く普及している。イギリスのテレビ局 BBC が製作したコメディ番組『空飛ぶモンティ・パイソン』にちなんで名付けられた。 (Pythonには、爬虫類のニシキヘビの意味があり、Python言語のマスコットやアイコンとして使われることがある。)" "\n"
                "" "\n"
                "## 概要" "\n"
                "プログラミング言語 Python は初心者から専門家まで幅広いユーザ層を獲得している。利用目的は汎用で、方向性としてはJavaに近い。ただし、最初からネットワーク利用をメインとして考えられているJavaよりセキュリティについてはやや寛大である。多くのプラットフォームをサポートしており（⇒[動作するプラットフォーム](#somelink))、豊富なライブラリがあることから、産業界でも利用が増えつつある。また、Pythonは純粋なプログラミング言語のほかにも、多くの異なる言語で書かれたモジュールをまとめる糊言語のひとつとして位置づけることができる。実際Pythonは多くの商用アプリケーションでスクリプト言語として採用されている（⇒Pythonを使っている製品あるいはソフトウェアの一覧）。豊富なドキュメントをもち、Unicodeによる文字列操作をサポートしており、日本語処理も標準で可能である。" "\n"
                "" "\n"
                "Python は基本的にインタプリタ上で実行されることを念頭において設計されており、以下のような特徴をもっている:" "\n"
                "" "\n"
                "* 動的な型付け。" "\n"
                "* オブジェクトのメンバに対するアクセスが制限されていない。（属性や専用のメソッドフックを実装することによって制限は可能。）" "\n"
                "* モジュール、クラス、オブジェクト等の言語の要素が内部からアクセス可能であり、リフレクションを利用した記述が可能。" "\n"
                "" "\n"
                "また、Pythonではインデントによりブロックを指定する構文を採用している（⇒[オフサイドルール](#jklj)）。この構文はPythonに慣れたユーザからは称賛をもって受け入れられているが、他の言語のユーザからは批判も多い。このほかにも、大きすぎる実行ファイルや、Javaに比べて遅い処理速度などが欠点として指摘されている。しかし **プロトタイピング** の際にはこれらの点はさして問題とはならないことから、研究開発部門では頻繁に利用されている。" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>パイソン (Python)</h1>" "\n"
                     R"(<p><strong>Python</strong>（パイソン）は、<a href="http://en.wikipedia.org/wiki/Guido_van_Rossum">Guido van Rossum</a> によって作られたオープンソースのオブジェクト指向スクリプト言語。<a href="http://ja.wikipedia.org/wiki/Perl">Perl</a>とともに欧米で広く普及している。イギリスのテレビ局 BBC が製作したコメディ番組『空飛ぶモンティ・パイソン』にちなんで名付けられた。 (Pythonには、爬虫類のニシキヘビの意味があり、Python言語のマスコットやアイコンとして使われることがある。)</p>)" "\n"
                     "<h2>概要</h2>" "\n"
                     R"(<p>プログラミング言語 Python は初心者から専門家まで幅広いユーザ層を獲得している。利用目的は汎用で、方向性としてはJavaに近い。ただし、最初からネットワーク利用をメインとして考えられているJavaよりセキュリティについてはやや寛大である。多くのプラットフォームをサポートしており（⇒<a href="#somelink">動作するプラットフォーム</a>)、豊富なライブラリがあることから、産業界でも利用が増えつつある。また、Pythonは純粋なプログラミング言語のほかにも、多くの異なる言語で書かれたモジュールをまとめる糊言語のひとつとして位置づけることができる。実際Pythonは多くの商用アプリケーションでスクリプト言語として採用されている（⇒Pythonを使っている製品あるいはソフトウェアの一覧）。豊富なドキュメントをもち、Unicodeによる文字列操作をサポートしており、日本語処理も標準で可能である。</p>)" "\n"
                     "<p>Python は基本的にインタプリタ上で実行されることを念頭において設計されており、以下のような特徴をもっている:</p>" "\n"
                     "<ul>" "\n"
                     "<li>動的な型付け。</li>" "\n"
                     "<li>オブジェクトのメンバに対するアクセスが制限されていない。（属性や専用のメソッドフックを実装することによって制限は可能。）</li>" "\n"
                     "<li>モジュール、クラス、オブジェクト等の言語の要素が内部からアクセス可能であり、リフレクションを利用した記述が可能。</li>" "\n"
                     "</ul>" "\n"
                     R"(<p>また、Pythonではインデントによりブロックを指定する構文を採用している（⇒<a href="#jklj">オフサイドルール</a>）。この構文はPythonに慣れたユーザからは称賛をもって受け入れられているが、他の言語のユーザからは批判も多い。このほかにも、大きすぎる実行ファイルや、Javaに比べて遅い処理速度などが欠点として指摘されている。しかし <strong>プロトタイピング</strong> の際にはこれらの点はさして問題とはならないことから、研究開発部門では頻繁に利用されている。</p>)"));
}

void TestMISC::lazy_block_quote()
{
    QString converted = this->md->convert(
                "> Line one of lazy block quote." "\n"
                "Line two of lazy block quote." "\n"
                "" "\n"
                "> Line one of paragraph two." "\n"
                "Line two of paragraph two." "\n"
                "");
    QCOMPARE(converted,
             QString("<blockquote>" "\n"
                     "<p>Line one of lazy block quote." "\n"
                     "Line two of lazy block quote.</p>" "\n"
                     "<p>Line one of paragraph two." "\n"
                     "Line two of paragraph two.</p>" "\n"
                     "</blockquote>"));
}

void TestMISC::link_with_parenthesis()
{
    QString converted = this->md->convert(
                R"([ZIP archives](http://en.wikipedia.org/wiki/ZIP_(file_format) "ZIP (file format) - Wikipedia, the free encyclopedia"))" "\n"
                "");
    QCOMPARE(converted,
             QString(R"raw(<p><a href="http://en.wikipedia.org/wiki/ZIP_(file_format)" title="ZIP (file format) - Wikipedia, the free encyclopedia">ZIP archives</a></p>)raw"));
}

void TestMISC::lists()
{
    QString converted = this->md->convert(
                "" "\n"
                "* A multi-paragraph list, " "\n"
                "unindented." "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "Simple tight list" "\n"
                "" "\n"
                "* Uno" "\n"
                "* Due" "\n"
                "* Tri" "\n"
                "" "\n"
                "A singleton tight list:" "\n"
                "" "\n"
                "* Uno" "\n"
                "" "\n"
                "A lose list:" "\n"
                "" "\n"
                "* One" "\n"
                "" "\n"
                "* Two" "\n"
                "" "\n"
                "* Three" "\n"
                "" "\n"
                "A lose list with paragraphs" "\n"
                "" "\n"
                "* One one one one" "\n"
                "" "\n"
                "    one one one one" "\n"
                "" "\n"
                "* Two two two two" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>A multi-paragraph list, " "\n"
                     "unindented.</li>" "\n"
                     "</ul>" "\n"
                     "<p>Simple tight list</p>" "\n"
                     "<ul>" "\n"
                     "<li>Uno</li>" "\n"
                     "<li>Due</li>" "\n"
                     "<li>Tri</li>" "\n"
                     "</ul>" "\n"
                     "<p>A singleton tight list:</p>" "\n"
                     "<ul>" "\n"
                     "<li>Uno</li>" "\n"
                     "</ul>" "\n"
                     "<p>A lose list:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>One</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>Two</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>Three</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>A lose list with paragraphs</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>One one one one</p>" "\n"
                     "<p>one one one one</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>Two two two two</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists2()
{
    QString converted = this->md->convert(
                "* blah blah blah" "\n"
                "sdf asdf asdf asdf asdf" "\n"
                "asda asdf asdfasd" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>blah blah blah" "\n"
                     "sdf asdf asdf asdf asdf" "\n"
                     "asda asdf asdfasd</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists3()
{
    QString converted = this->md->convert(
                "* blah blah blah" "\n"
                "    sdf asdf asdf asdf asdf" "\n"
                "    asda asdf asdfasd" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>blah blah blah" "\n"
                     "    sdf asdf asdf asdf asdf" "\n"
                     "    asda asdf asdfasd</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists4()
{
    QString converted = this->md->convert(
                "" "\n"
                "* item1" "\n"
                "* item2" "\n"
                "    1. Number 1" "\n"
                "    2. Number 2" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>item1</li>" "\n"
                     "<li>item2<ol>" "\n"
                     "<li>Number 1</li>" "\n"
                     "<li>Number 2</li>" "\n"
                     "</ol>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists5()
{
    QString converted = this->md->convert(
                "> This is a test of a block quote" "\n"
                "> With just two lines" "\n"
                "" "\n"
                "A paragraph" "\n"
                "" "\n"
                "> This is a more difficult case" "\n"
                "> With a list item inside the quote" "\n"
                ">" "\n"
                "> * Alpha" "\n"
                "> * Beta" "\n"
                "> Etc." "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<blockquote>" "\n"
                     "<p>This is a test of a block quote" "\n"
                     "With just two lines</p>" "\n"
                     "</blockquote>" "\n"
                     "<p>A paragraph</p>" "\n"
                     "<blockquote>" "\n"
                     "<p>This is a more difficult case" "\n"
                     "With a list item inside the quote</p>" "\n"
                     "<ul>" "\n"
                     "<li>Alpha</li>" "\n"
                     "<li>Beta" "\n"
                     "Etc.</li>" "\n"
                     "</ul>" "\n"
                     "</blockquote>"));
}

void TestMISC::lists6()
{
    QString converted = this->md->convert(
                "Test five or more spaces as start of list:" "\n"
                "" "\n"
                "*     five spaces" "\n"
                "" "\n"
                "not first item:" "\n"
                "" "\n"
                "* one space" "\n"
                "*     five spaces" "\n"
                "" "\n"
                "loose list:" "\n"
                "" "\n"
                "* one space" "\n"
                "" "\n"
                "*     five spaces" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Test five or more spaces as start of list:</p>" "\n"
                     "<ul>" "\n"
                     "<li>five spaces</li>" "\n"
                     "</ul>" "\n"
                     "<p>not first item:</p>" "\n"
                     "<ul>" "\n"
                     "<li>one space</li>" "\n"
                     "<li>five spaces</li>" "\n"
                     "</ul>" "\n"
                     "<p>loose list:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>one space</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>five spaces</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists7()
{
    QString converted = this->md->convert(
                "* item 1" "\n"
                "*   * item 2-1" "\n"
                "    * item 2-2" "\n"
                "    * item 2-3" "\n"
                "    * item 2-4" "\n"
                "* item 3" "\n"
                "*   * item 4-1" "\n"
                "" "\n"
                "    * item 4-2" "\n"
                "" "\n"
                "    * item 4-3" "\n"
                "" "\n"
                "    * item 4-4" "\n"
                "" "\n"
                "## same as above, different spacing" "\n"
                "* item 1" "\n"
                "* * item 2-1" "\n"
                "    * item 2-2" "\n"
                "* item 3" "\n"
                "* * item 4-1" "\n"
                "" "\n"
                "     * item 4-2" "\n"
                "" "\n"
                "## only 1 item in nested list ## " "\n"
                "* item 1" "\n"
                "* * item 2-1" "\n"
                "* item 3" "\n"
                "* * item 4-1" "\n"
                "" "\n"
                "## Something ludicrous ## " "\n"
                "* item 1" "\n"
                "* * item 2-1" "\n"
                "    * item 2-2" "\n"
                "    * * item 2-2-1" "\n"
                "        * item 2-2-2" "\n"
                "    * item 2-3" "\n"
                "* item 3" "\n"
                "* * item 4-1" "\n"
                "" "\n"
                "    * * item 4-1-1" "\n"
                "        * item 4-1-2" "\n"
                "" "\n"
                "    * item 4-2" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>item 1</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-1</li>" "\n"
                     "<li>item 2-2</li>" "\n"
                     "<li>item 2-3</li>" "\n"
                     "<li>item 2-4</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 3</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>item 4-1</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-2</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-3</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-4</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<h2>same as above, different spacing</h2>" "\n"
                     "<ul>" "\n"
                     "<li>item 1</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-1</li>" "\n"
                     "<li>item 2-2</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 3</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>item 4-1</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-2</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<h2>only 1 item in nested list ##</h2>" "\n"
                     "<ul>" "\n"
                     "<li>item 1</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-1</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 3</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 4-1</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<h2>Something ludicrous ##</h2>" "\n"
                     "<ul>" "\n"
                     "<li>item 1</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-1</li>" "\n"
                     "<li>item 2-2</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-2-1</li>" "\n"
                     "<li>item 2-2-2</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 2-3</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 3</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>item 4-1</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<ul>" "\n"
                     "<li>item 4-1-1</li>" "\n"
                     "<li>item 4-1-2</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-2</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::lists8()
{
    QString converted = this->md->convert(
                "# Lists with blockquotes" "\n"
                "1. > Four-score and seven years ago..." "\n"
                "" "\n"
                "2. > We have nothing to fear..." "\n"
                "" "\n"
                "3. > This is it..." "\n"
                "" "\n"
                "# Multi-line blockquotes" "\n"
                "* > Four-score and sever years ago" "\n"
                "  > our fathers brought forth" "\n"
                "" "\n"
                "* > We have nothing to fear" "\n"
                "  > but fear itself" "\n"
                "" "\n"
                "* > This is it" "\n"
                "  > as far as I'm concerned" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>Lists with blockquotes</h1>" "\n"
                     "<ol>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>Four-score and seven years ago...</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>We have nothing to fear...</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>This is it...</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "</ol>" "\n"
                     "<h1>Multi-line blockquotes</h1>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>Four-score and sever years ago" "\n"
                     "our fathers brought forth</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>We have nothing to fear" "\n"
                     "but fear itself</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<blockquote>" "\n"
                     "<p>This is it" "\n"
                     "as far as I'm concerned</p>" "\n"
                     "</blockquote>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::markup_inside_p()
{
    QString converted = this->md->convert(
                "<p>" "\n"
                "" "\n"
                "_foo_" "\n"
                "" "\n"
                "</p>" "\n"
                "" "\n"
                "<p>" "\n"
                "_foo_" "\n"
                "</p>" "\n"
                "" "\n"
                "<p>_foo_</p>" "\n"
                "" "\n"
                "<p>" "\n"
                "" "\n"
                "_foo_" "\n"
                "</p>" "\n"
                "" "\n"
                "<p>" "\n"
                "_foo_" "\n"
                "" "\n"
                "</p>" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>" "\n"
                     "" "\n"
                     "_foo_" "\n"
                     "" "\n"
                     "</p>" "\n"
                     "" "\n"
                     "<p>" "\n"
                     "_foo_" "\n"
                     "</p>" "\n"
                     "" "\n"
                     "<p>_foo_</p>" "\n"
                     "" "\n"
                     "<p>" "\n"
                     "" "\n"
                     "_foo_" "\n"
                     "</p>" "\n"
                     "" "\n"
                     "<p>" "\n"
                     "_foo_" "\n"
                     "" "\n"
                     "</p>"));
}

void TestMISC::mismatched_tags()
{
    QString converted = this->md->convert(
                "<p>Some text</p><div>some more text</div>" "\n"
                "" "\n"
                "and a bit more" "\n"
                "" "\n"
                "<p>And this output</p> *Compatible with PHP Markdown Extra 1.2.2 and Markdown.pl1.0.2b8:*" "\n"
                "" "\n"
                "<!-- comment --><p><div>text</div><br /></p><br />" "\n"
                "" "\n"
                "Should be in p" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Some text</p>" "\n"
                     "" "\n"
                     "<div>some more text</div>" "\n"
                     "" "\n"
                     "<p>and a bit more</p>" "\n"
                     "<p>And this output</p>" "\n"
                     "" "\n"
                     "<p><em>Compatible with PHP Markdown Extra 1.2.2 and Markdown.pl1.0.2b8:</em></p>" "\n"
                     "<!-- comment -->" "\n"
                     "" "\n"
                     "<p><div>text</div><br /></p>" "\n"
                     "" "\n"
                     "<p><br /></p>" "\n"
                     "<p>Should be in p</p>"));
}

void TestMISC::missing_link_def()
{
    QString converted = this->md->convert(
                "This is a [missing link][empty] and a [valid][link] and [missing][again]." "\n"
                "" "\n"
                "[link]: http://example.com" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p>This is a [missing link][empty] and a <a href="http://example.com">valid</a> and [missing][again].</p>)"));
}

void TestMISC::more_comments()
{
    QString converted = this->md->convert(
                "<!asd@asdfd.com>" "\n"
                "" "\n"
                "Foo" "\n"
                "" "\n"
                "<asd!@asdfd.com>" "\n"
                "" "\n"
                "Bar" "\n"
                "" "\n"
                "<!--asd@asdfd.com>" "\n"
                "" "\n"
                "Still in unclosed comment" "\n"
                "");
    QCOMPARE(converted,
             QString("<!asd@asdfd.com>" "\n"
                     "" "\n"
                     "<p>Foo</p>" "\n"
                     "<p><asd!@asdfd.com></p>" "\n"
                     "<p>Bar</p>" "\n"
                     "<!--asd@asdfd.com>" "\n"
                     "" "\n"
                     "Still in unclosed comment"));
}

void TestMISC::multi_line_tags()
{
    QString converted = this->md->convert(
                "" "\n"
                "<div>" "\n"
                "" "\n"
                "asdf asdfasd" "\n"
                "" "\n"
                "</div>" "\n"
                "" "\n"
                "<div>" "\n"
                "" "\n"
                "foo bar" "\n"
                "" "\n"
                "</div>" "\n"
                "No blank line." "\n"
                "");
    QCOMPARE(converted,
             QString("<div>" "\n"
                     "" "\n"
                     "asdf asdfasd" "\n"
                     "" "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<div>" "\n"
                     "" "\n"
                     "foo bar" "\n"
                     "" "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<p>No blank line.</p>"));
}

void TestMISC::multi_paragraph_block_quote()
{
    QString converted = this->md->convert(
                "> This is line one of paragraph one" "\n"
                "> This is line two of paragraph one" "\n"
                "" "\n"
                "> This is line one of paragraph two" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "> This is another blockquote." "\n"
                "");
    QCOMPARE(converted,
             QString("<blockquote>" "\n"
                     "<p>This is line one of paragraph one" "\n"
                     "This is line two of paragraph one</p>" "\n"
                     "<p>This is line one of paragraph two</p>" "\n"
                     "<p>This is another blockquote.</p>" "\n"
                     "</blockquote>"));
}

void TestMISC::multi_test()
{
    QString converted = this->md->convert(
                "" "\n"
                "# Header {@id=inthebeginning}" "\n"
                "" "\n"
                "Now, let's try something *inline{@class=special}*, to see if it works" "\n"
                "" "\n"
                "" "\n"
                "Blah blah blah <http://www.slashdot.org>" "\n"
                "" "\n"
                "* Basic list" "\n"
                "* Basic list 2" "\n"
                "" "\n"
                "addss" "\n"
                "" "\n"
                " * Lazy list" "\n"
                "" "\n"
                "An [example][ref] (oops)" "\n"
                "" "\n"
                R"(  [ref]: http://example.com  "Title" )" "\n"
                "" "\n"
                "" "\n"
                "Now, let's use a footnote[^1].  Not bad, eh?" "\n"
                "Let's continue." "\n"
                "" "\n"
                "  [^1]: Here is the text of the footnote" "\n"
                "    continued on several lines." "\n"
                "    some more of the footnote, etc." "\n"
                "" "\n"
                "    Actually, another paragraph too." "\n"
                "" "\n"
                "And then there is a little bit of text." "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<h1 id="inthebeginning">Header </h1>)" "\n"
                     R"(<p>Now, let's try something <em class="special">inline</em>, to see if it works</p>)" "\n"
                     R"(<p>Blah blah blah <a href="http://www.slashdot.org">http://www.slashdot.org</a></p>)" "\n"
                     "<ul>" "\n"
                     "<li>Basic list</li>" "\n"
                     "<li>Basic list 2</li>" "\n"
                     "</ul>" "\n"
                     "<p>addss</p>" "\n"
                     "<ul>" "\n"
                     "<li>Lazy list</li>" "\n"
                     "</ul>" "\n"
                     R"(<p>An <a href="http://example.com" title="Title">example</a> (oops)</p>)" "\n"
                     "<p>Now, let's use a footnote[^1].  Not bad, eh?" "\n"
                     "Let's continue.</p>" "\n"
                     "<p>[^1]: Here is the text of the footnote" "\n"
                     "    continued on several lines." "\n"
                     "    some more of the footnote, etc.</p>" "\n"
                     "<pre><code>Actually, another paragraph too." "\n"
                     "</code></pre>" "\n"
                     "<p>And then there is a little bit of text.</p>"));
}

void TestMISC::multiline_comments()
{
    QString converted = this->md->convert(
                "<!--" "\n"
                "" "\n"
                "foo" "\n"
                "" "\n"
                "--> " "\n"
                "" "\n"
                "<p>" "\n"
                "" "\n"
                "foo" "\n"
                "" "\n"
                "</p>" "\n"
                "" "\n"
                "" "\n"
                "<div>" "\n"
                "" "\n"
                "foo" "\n"
                "" "\n"
                "</div>" "\n"
                "" "\n"
                "<!-- foo" "\n"
                "" "\n"
                "-->" "\n"
                "" "\n"
                "<!-- <tag>" "\n"
                "" "\n"
                "-->" "\n"
                "" "\n"
                "<!--" "\n"
                "" "\n"
                "foo -->" "\n"
                "" "\n"
                "<!--" "\n"
                "" "\n"
                "<tag> -->" "\n"
                "" "\n"
                "<!-- unclosed comment" "\n"
                "" "\n"
                "__Still__ a comment (browsers see it that way)" "\n"
                "");
    QCOMPARE(converted,
             QString("<!--" "\n"
                     "" "\n"
                     "foo" "\n"
                     "" "\n"
                     "-->" "\n"
                     "" "\n"
                     "<p>" "\n"
                     "" "\n"
                     "foo" "\n"
                     "" "\n"
                     "</p>" "\n"
                     "" "\n"
                     "<div>" "\n"
                     "" "\n"
                     "foo" "\n"
                     "" "\n"
                     "</div>" "\n"
                     "" "\n"
                     "<!-- foo" "\n"
                     "" "\n"
                     "-->" "\n"
                     "" "\n"
                     "<!-- <tag>" "\n"
                     "" "\n"
                     "-->" "\n"
                     "" "\n"
                     "<!--" "\n"
                     "" "\n"
                     "foo -->" "\n"
                     "" "\n"
                     "<!--" "\n"
                     "" "\n"
                     "<tag> -->" "\n"
                     "" "\n"
                     "<!-- unclosed comment" "\n"
                     "" "\n"
                     "__Still__ a comment (browsers see it that way)"));
}

void TestMISC::nested_lists()
{
    QString converted = this->md->convert(
                "* item 1" "\n"
                "" "\n"
                "    paragraph 2" "\n"
                "" "\n"
                "* item 2" "\n"
                "" "\n"
                "    * item 2-1" "\n"
                "    * item 2-2" "\n"
                "" "\n"
                "        * item 2-2-1" "\n"
                "" "\n"
                "    * item 2-3" "\n"
                "" "\n"
                "        * item 2-3-1" "\n"
                "" "\n"
                "* item 3" "\n"
                "" "\n"
                "plain text" "\n"
                "" "\n"
                "* item 1" "\n"
                "    * item 1-1" "\n"
                "    * item 1-2" "\n"
                "        * item 1-2-1" "\n"
                "* item 2" "\n"
                "* item 3" "\n"
                "* item 4" "\n"
                "    * item 4-1" "\n"
                "    * item 4-2" "\n"
                "    * item 4-3" "\n"
                "" "\n"
                "        Paragraph under item 4-3" "\n"
                "" "\n"
                "    Paragraph under item 4" "\n"
                "");
    QCOMPARE(converted,
             QString("<ul>" "\n"
                     "<li>" "\n"
                     "<p>item 1</p>" "\n"
                     "<p>paragraph 2</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 2</p>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-1</li>" "\n"
                     "<li>" "\n"
                     "<p>item 2-2</p>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-2-1</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 2-3</p>" "\n"
                     "<ul>" "\n"
                     "<li>item 2-3-1</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>item 3</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>plain text</p>" "\n"
                     "<ul>" "\n"
                     "<li>item 1<ul>" "\n"
                     "<li>item 1-1</li>" "\n"
                     "<li>item 1-2<ul>" "\n"
                     "<li>item 1-2-1</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>item 2</li>" "\n"
                     "<li>item 3</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4</p>" "\n"
                     "<ul>" "\n"
                     "<li>item 4-1</li>" "\n"
                     "<li>item 4-2</li>" "\n"
                     "<li>" "\n"
                     "<p>item 4-3</p>" "\n"
                     "<p>Paragraph under item 4-3</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>Paragraph under item 4</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}

void TestMISC::nested_patterns()
{
    QString converted = this->md->convert(
                "___[link](http://example.com)___" "\n"
                "***[link](http://example.com)***" "\n"
                "**[*link*](http://example.com)**" "\n"
                "__[_link_](http://example.com)__" "\n"
                "__[*link*](http://example.com)__" "\n"
                "**[_link_](http://example.com)**" "\n"
                "[***link***](http://example.com)" "\n"
                "" "\n"
                "***I am ___italic_ and__ bold* I am `just` bold**" "\n"
                "" "\n"
                "Example __*bold italic*__ on the same line __*bold italic*__." "\n"
                "" "\n"
                "Example **_bold italic_** on the same line **_bold italic_**." "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><strong><em><a href="http://example.com">link</a></em></strong>)" "\n"
                     R"(<strong><em><a href="http://example.com">link</a></em></strong>)" "\n"
                     R"(<strong><a href="http://example.com"><em>link</em></a></strong>)" "\n"
                     R"(<strong><a href="http://example.com"><em>link</em></a></strong>)" "\n"
                     R"(<strong><a href="http://example.com"><em>link</em></a></strong>)" "\n"
                     R"(<strong><a href="http://example.com"><em>link</em></a></strong>)" "\n"
                     R"(<a href="http://example.com"><strong><em>link</em></strong></a></p>)" "\n"
                     "<p><strong><em>I am <strong><em>italic</em> and</strong> bold</em> I am <code>just</code> bold</strong></p>" "\n"
                     "<p>Example <strong><em>bold italic</em></strong> on the same line <strong><em>bold italic</em></strong>.</p>" "\n"
                     "<p>Example <strong><em>bold italic</em></strong> on the same line <strong><em>bold italic</em></strong>.</p>"));
}

void TestMISC::normalize()
{
    QString converted = this->md->convert(
                "" "\n"
                "[Link](http://www.stuff.com/q?x=1&y=2<>)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://www.stuff.com/q?x=1&amp;y=2&lt;&gt;">Link</a></p>)"));
}

void TestMISC::numeric_entity()
{
    QString converted = this->md->convert(
                "" "\n"
                "<user@gmail.com>" "\n"
                "" "\n"
                "This is an entity: &#234; " "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="&#109;&#97;&#105;&#108;&#116;&#111;&#58;&#117;&#115;&#101;&#114;&#64;&#103;&#109;&#97;&#105;&#108;&#46;&#99;&#111;&#109;">&#117;&#115;&#101;&#114;&#64;&#103;&#109;&#97;&#105;&#108;&#46;&#99;&#111;&#109;</a></p>)" "\n"
                     "<p>This is an entity: &#234; </p>"));
}

void TestMISC::para_with_hr()
{
    QString converted = this->md->convert(
                "Here is a paragraph, followed by a horizontal rule." "\n"
                "***" "\n"
                "Followed by another paragraph." "\n"
                "" "\n"
                "Here is another paragraph, followed by:" "\n"
                "*** not an HR." "\n"
                "Followed by more of the same paragraph." "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Here is a paragraph, followed by a horizontal rule.</p>" "\n"
                     "<hr />" "\n"
                     "<p>Followed by another paragraph.</p>" "\n"
                     "<p>Here is another paragraph, followed by:" "\n"
                     "*** not an HR." "\n"
                     "Followed by more of the same paragraph.</p>"));
}

void TestMISC::php()
{
    QString converted = this->md->convert(
                R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN")" "\n"
                R"(            "http://www.w3.org/TR/html4/strict.dtd">)" "\n"
                "" "\n"
                "<b>This should have a p tag</b>" "\n"
                "" "\n"
                "<!--This is a comment -->" "\n"
                "" "\n"
                "<div>This shouldn't</div>" "\n"
                "" "\n"
                R"(<?php echo "block_level";?>)" "\n"
                "" "\n"
                R"( <?php echo "not_block_level";?>)" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN")" "\n"
                     R"(            "http://www.w3.org/TR/html4/strict.dtd">)" "\n"
                     "" "\n"
                     "<p><b>This should have a p tag</b></p>" "\n"
                     "<!--This is a comment -->" "\n"
                     "" "\n"
                     "<div>This shouldn't</div>" "\n"
                     "" "\n"
                     R"(<?php echo "block_level";?>)" "\n"
                     "" "\n"
                     R"(<p>&lt;?php echo "not_block_level";?&gt;</p>)"));
}

void TestMISC::pre()
{
    QString converted = this->md->convert(
                "<pre>" "\n"
                "" "\n"
                "aaa" "\n"
                "" "\n"
                "bbb" "\n"
                "</pre>" "\n"
                "" "\n"
                "<pre>" "\n"
                "* and this is pre-formatted content" "\n"
                "* and it should be printed just like this" "\n"
                "* and not formatted as a list" "\n"
                "" "\n"
                "</pre>" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<pre>" "\n"
                     "" "\n"
                     "aaa" "\n"
                     "" "\n"
                     "bbb" "\n"
                     "</pre>" "\n"
                     "" "\n"
                     "<pre>" "\n"
                     "* and this is pre-formatted content" "\n"
                     "* and it should be printed just like this" "\n"
                     "* and not formatted as a list" "\n"
                     "" "\n"
                     "</pre>"));
}

void TestMISC::raw_whitespace()
{
    QString converted = this->md->convert(
                "Preserve whitespace in raw html" "\n"
                "" "\n"
                "<pre>" "\n"
                "class Foo():" "\n"
                "    bar = 'bar'" "\n"
                "" "\n"
                "    def baz(self):" "\n"
                "        print self.bar" "\n"
                "</pre>" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Preserve whitespace in raw html</p>" "\n"
                     "<pre>" "\n"
                     "class Foo():" "\n"
                     "    bar = 'bar'" "\n"
                     "" "\n"
                     "    def baz(self):" "\n"
                     "        print self.bar" "\n"
                     "</pre>"));
}

void TestMISC::russian()
{
    QString converted = this->md->convert(
                "Недвард «Нед» Фландерс" "\n"
                "======================" "\n"
                "" "\n"
                "" "\n"
                "**Недвард «Нед» Фландерс** (Nedward «Ned» Flanders) — вымышленный персонаж мультсериала «[Симпсоны][]», озвученный Гарри Ширером. Он и его семья живут по соседству от семьи Симпсонов. Набожный христианин, Нед является одним из столпов морали Спрингфилда. В эпизоде «Alone Again, Natura-Diddily»  он овдовел, его жена Мод погибла в результате несчастного случая. " "\n"
                "" "\n"
                "Нед был одним из первых персонажей в мультсериале, который не был членом семьи Симпсонов. Начиная с первых серий, он регулярно появляется в «Симпсонах». Считается, что Нед Фландерс был назван в честь улицы *Northeast Flanders St.* в [Портленде](http://www.portland.gov), Орегон, родном городе создателя мультсериала Мэтта Грейнинга]]. Надпись на указателе улицы *NE Flanders St.* хулиганы часто исправляли на _NED Flanders St._" "\n"
                "" "\n"
                "## Биография" "\n"
                "" "\n"
                "Нед Фландерс родился в Нью-Йорке, его родители были битниками. Его отец в точности похож на взрослого Неда, только он носил козлиную бородку. Их отказ от воспитания Неда и то, что они, в общем-то, были плохими родителями («мы ничего в этом не понимаем и не знаем как начать») привело к тому, что Нед превратился в ужасного сорванца. В конце концов они согласились на экспериментальную восьмимесячную шлепологическую терапию Миннесотского Университета (воспоминания Неда в эпизоде «Hurricane Neddy»), которая научила его подавлять чувство злости. Побочным эфектом терапии стало то, что Нед стал ненавидеть своих родителей (это одна из двух вещей которые ненавидит Фландерс, вторая — отделения почты, чьи длинные очереди, суета и угрюмый персонал раздражают его)." "\n"
                "" "\n"
                "У Неда есть странная привычка добавлять «дидли», «дадли» и другие бессмысленные слова в свои фразы при разговоре, например: «Hi-diddly-ho, neighbor-ino» («Приветик, соседушка»). Это результат сублимации его злости, вызванной сдерживанием гнева, который не имеет никакого другого выхода." "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<h1>Недвард «Нед» Фландерс</h1>" "\n"
                     "<p><strong>Недвард «Нед» Фландерс</strong> (Nedward «Ned» Flanders) — вымышленный персонаж мультсериала «[Симпсоны][]», озвученный Гарри Ширером. Он и его семья живут по соседству от семьи Симпсонов. Набожный христианин, Нед является одним из столпов морали Спрингфилда. В эпизоде «Alone Again, Natura-Diddily»  он овдовел, его жена Мод погибла в результате несчастного случая. </p>" "\n"
                     R"(<p>Нед был одним из первых персонажей в мультсериале, который не был членом семьи Симпсонов. Начиная с первых серий, он регулярно появляется в «Симпсонах». Считается, что Нед Фландерс был назван в честь улицы <em>Northeast Flanders St.</em> в <a href="http://www.portland.gov">Портленде</a>, Орегон, родном городе создателя мультсериала Мэтта Грейнинга]]. Надпись на указателе улицы <em>NE Flanders St.</em> хулиганы часто исправляли на <em>NED Flanders St.</em></p>)" "\n"
                     "<h2>Биография</h2>" "\n"
                     "<p>Нед Фландерс родился в Нью-Йорке, его родители были битниками. Его отец в точности похож на взрослого Неда, только он носил козлиную бородку. Их отказ от воспитания Неда и то, что они, в общем-то, были плохими родителями («мы ничего в этом не понимаем и не знаем как начать») привело к тому, что Нед превратился в ужасного сорванца. В конце концов они согласились на экспериментальную восьмимесячную шлепологическую терапию Миннесотского Университета (воспоминания Неда в эпизоде «Hurricane Neddy»), которая научила его подавлять чувство злости. Побочным эфектом терапии стало то, что Нед стал ненавидеть своих родителей (это одна из двух вещей которые ненавидит Фландерс, вторая — отделения почты, чьи длинные очереди, суета и угрюмый персонал раздражают его).</p>" "\n"
                     "<p>У Неда есть странная привычка добавлять «дидли», «дадли» и другие бессмысленные слова в свои фразы при разговоре, например: «Hi-diddly-ho, neighbor-ino» («Приветик, соседушка»). Это результат сублимации его злости, вызванной сдерживанием гнева, который не имеет никакого другого выхода.</p>"));
}

void TestMISC::smart_em()
{
    QString converted = this->md->convert(
                "_emphasis_" "\n"
                "" "\n"
                "this_is_not_emphasis" "\n"
                "" "\n"
                "[_punctuation with emphasis_]" "\n"
                "" "\n"
                "[_punctuation_with_emphasis_]" "\n"
                "" "\n"
                "[punctuation_without_emphasis]" "\n"
                "");
    QCOMPARE(converted,
             QString("<p><em>emphasis</em></p>" "\n"
                     "<p>this_is_not_emphasis</p>" "\n"
                     "<p>[<em>punctuation with emphasis</em>]</p>" "\n"
                     "<p>[<em>punctuation_with_emphasis</em>]</p>" "\n"
                     "<p>[punctuation_without_emphasis]</p>"));
}

void TestMISC::some_test()
{
    QString converted = this->md->convert(
                "----------------------" "\n"
                "" "\n"
                "* as if" "\n"
                "\t" "\n"
                "* as if2" "\n"
                "" "\n"
                "----------------------" "\n"
                "" "\n"
                "* as if" "\n"
                "    " "\n"
                "* as if2" "\n"
                "" "\n"
                "----------------------" "\n"
                "" "\n"
                "* as if" "\n"
                "    non_code" "\n"
                "* as if2" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "Markdown" "\n"
                "" "\n"
                "*   Python" "\n"
                "    is ok" "\n"
                "    * Therefore i am" "\n"
                "" "\n"
                "* Perl sucks" "\n"
                "    big time" "\n"
                "    * But that's" "\n"
                "    ok" "\n"
                "" "\n"
                "* Python is" "\n"
                "ok" "\n"
                "    Or not?" "\n"
                "   " "\n"
                "Here is a normal paragraph" "\n"
                "" "\n"
                "1. Another list" "\n"
                "with a bunch of items" "\n"
                "2. Mostly fruits" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                "    3. Apple" "\n"
                "    4. Pare" "\n"
                "" "\n"
                "asdfasdfasd" "\n"
                "" "\n"
                "" "\n"
                "    # This is a code example" "\n"
                "    import stuff" "\n"
                "" "\n"
                "    Another code example" "\n"
                "    * Lists and similar stuff" "\n"
                "" "\n"
                "    > Should be ignored" "\n"
                "");
    QCOMPARE(converted,
             QString("<hr />" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>as if</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>as if2</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<hr />" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>as if</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>as if2</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<hr />" "\n"
                     "<ul>" "\n"
                     "<li>as if" "\n"
                     "    non_code</li>" "\n"
                     "<li>as if2</li>" "\n"
                     "</ul>" "\n"
                     "<p>Markdown</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>Python" "\n"
                     "    is ok</p>" "\n"
                     "<ul>" "\n"
                     "<li>Therefore i am</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>Perl sucks" "\n"
                     "    big time</p>" "\n"
                     "<ul>" "\n"
                     "<li>But that's" "\n"
                     "ok</li>" "\n"
                     "</ul>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>Python is" "\n"
                     "ok" "\n"
                     "    Or not?</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>Here is a normal paragraph</p>" "\n"
                     "<ol>" "\n"
                     "<li>Another list" "\n"
                     "with a bunch of items</li>" "\n"
                     "<li>" "\n"
                     "<p>Mostly fruits</p>" "\n"
                     "<ol>" "\n"
                     "<li>Apple</li>" "\n"
                     "<li>Pare</li>" "\n"
                     "</ol>" "\n"
                     "</li>" "\n"
                     "</ol>" "\n"
                     "<p>asdfasdfasd</p>" "\n"
                     "<pre><code># This is a code example" "\n"
                     "import stuff" "\n"
                     "" "\n"
                     "Another code example" "\n"
                     "* Lists and similar stuff" "\n"
                     "" "\n"
                     "&gt; Should be ignored" "\n"
                     "</code></pre>"));
}

void TestMISC::span()
{
    QString converted = this->md->convert(
                "" "\n"
                R"(<span id="someId"> Foo *bar* Baz </span>)" "\n"
                "" "\n"
                "<div><b>*foo*</b></div>" "\n"
                "" "\n"
                R"(<div id="someId"> Foo *bar* Baz </div>)" "\n"
                "" "\n"
                R"(<baza id="someId"> Foo *bar* Baz </baza>)" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><span id="someId"> Foo <em>bar</em> Baz </span></p>)" "\n"
                     "<div><b>*foo*</b></div>" "\n"
                     "" "\n"
                     R"(<div id="someId"> Foo *bar* Baz </div>)" "\n"
                     "" "\n"
                     R"(<p><baza id="someId"> Foo <em>bar</em> Baz </baza></p>)"));
}

void TestMISC::strong_with_underscores()
{
    QString converted = this->md->convert(
                "__this_is_strong__" "\n"
                "");
    QCOMPARE(converted,
             QString("<p><strong>this_is_strong</strong></p>"));
}

void TestMISC::stronintags()
{
    QString converted = this->md->convert(
                "this is a [**test**](http://example.com/)" "\n"
                "" "\n"
                "this is a second **[test](http://example.com)**" "\n"
                "" "\n"
                "reference **[test][]**" "\n"
                "reference [**test**][]" "\n"
                "" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p>this is a <a href="http://example.com/"><strong>test</strong></a></p>)" "\n"
                     R"(<p>this is a second <strong><a href="http://example.com">test</a></strong></p>)" "\n"
                     "<p>reference <strong>[test][]</strong>" "\n"
                     "reference [<strong>test</strong>][]</p>"));
}

void TestMISC::tabs_in_lists()
{
    QString converted = this->md->convert(
                "First a list with a tabbed line" "\n"
                "" "\n"
                "* A" "\n"
                "\t" "\n"
                "* B" "\n"
                "" "\n"
                "Just a blank line:" "\n"
                "" "\n"
                "* A" "\n"
                "" "\n"
                "* B" "\n"
                "" "\n"
                "" "\n"
                "Now a list with 4 spaces and some text:" "\n"
                "" "\n"
                "* A" "\n"
                "    abcdef" "\n"
                "* B" "\n"
                "" "\n"
                "" "\n"
                "Now with a tab and an extra space:" "\n"
                "" "\n"
                "* A" "\n"
                "\t " "\n"
                "* B" "\n"
                "" "\n"
                "Now a list with 4 spaces:" "\n"
                "" "\n"
                "* A" "\n"
                "    " "\n"
                "* B" "\n"
                "" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>First a list with a tabbed line</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>A</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>B</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>Just a blank line:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>A</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>B</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>Now a list with 4 spaces and some text:</p>" "\n"
                     "<ul>" "\n"
                     "<li>A" "\n"
                     "    abcdef</li>" "\n"
                     "<li>B</li>" "\n"
                     "</ul>" "\n"
                     "<p>Now with a tab and an extra space:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>A</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>B</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>Now a list with 4 spaces:</p>" "\n"
                     "<ul>" "\n"
                     "<li>" "\n"
                     "<p>A</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>B</p>" "\n"
                     "</li>" "\n"
                     "</ul>"));
}
void TestMISC::two_spaces()
{
    QString converted = this->md->convert(
                "This line has two spaces at the end  " "\n"
                "but this one has none" "\n"
                "but this line has three   " "\n"
                "and this is the second from last line" "\n"
                "in this test message" "\n"
                "" "\n"
                "* This list item has two spaces.  " "\n"
                "* This has none." "\n"
                "    This line has three.   " "\n"
                "    This line has none." "\n"
                "    And this line two.  " "\n"
                "" "\n"
                "    This line has none." "\n"
                "" "\n"
                "* This line has none." "\n"
                "" "\n"
                "And this is the end." "\n"
                "");
    QCOMPARE(converted,
             QString("<p>This line has two spaces at the end<br />" "\n"
                     "but this one has none" "\n"
                     "but this line has three <br />" "\n"
                     "and this is the second from last line" "\n"
                     "in this test message</p>" "\n"
                     "<ul>" "\n"
                     "<li>This list item has two spaces.  </li>" "\n"
                     "<li>" "\n"
                     "<p>This has none." "\n"
                     "    This line has three. <br />" "\n"
                     "    This line has none." "\n"
                     "    And this line two.  </p>" "\n"
                     "<p>This line has none.</p>" "\n"
                     "</li>" "\n"
                     "<li>" "\n"
                     "<p>This line has none.</p>" "\n"
                     "</li>" "\n"
                     "</ul>" "\n"
                     "<p>And this is the end.</p>"));
}

void TestMISC::uche()
{
    QString converted = this->md->convert(
                R"(![asif](http://fourthought.com/images/ftlogo.png "Fourthought logo"))" "\n"
                "" "\n"
                "[![{@style=float: left; margin: 10px; border:" "\n"
                R"(none;}](http://fourthought.com/images/ftlogo.png "Fourthought)" "\n"
                R"(logo")](http://fourthought.com/))" "\n"
                "" "\n"
                "[![text](x)](http://link.com/)" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><img alt="asif" src="http://fourthought.com/images/ftlogo.png" title="Fourthought logo" /></p>)" "\n"
                     R"(<p><a href="http://fourthought.com/"><img alt="" src="http://fourthought.com/images/ftlogo.png" style="float: left; margin: 10px; border: none;" title="Fourthought logo" /></a></p>)" "\n"
                     R"(<p><a href="http://link.com/"><img alt="text" src="x" /></a></p>)"));
}

void TestMISC::underscores()
{
    QString converted = this->md->convert(
                "THIS_SHOULD_STAY_AS_IS" "\n"
                "" "\n"
                "Here is some _emphasis_, ok?" "\n"
                "" "\n"
                "Ok, at least _this_ should work." "\n"
                "" "\n"
                "THIS__SHOULD__STAY" "\n"
                "" "\n"
                "Here is some __strong__ stuff." "\n"
                "" "\n"
                "THIS___SHOULD___STAY?" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>THIS_SHOULD_STAY_AS_IS</p>" "\n"
                     "<p>Here is some <em>emphasis</em>, ok?</p>" "\n"
                     "<p>Ok, at least <em>this</em> should work.</p>" "\n"
                     "<p>THIS<strong>SHOULD</strong>STAY</p>" "\n"
                     "<p>Here is some <strong>strong</strong> stuff.</p>" "\n"
                     "<p>THIS<strong><em>SHOULD</em></strong>STAY?</p>"));
}

void TestMISC::url_spaces()
{
    QString converted = this->md->convert(
                "[Dawn of War](http://wikipedia.org/wiki/Dawn of War)" "\n"
                "" "\n"
                "" "\n"
                R"([Dawn of War](http://wikipedia.org/wiki/Dawn of War "Dawn of War"))" "\n"
                "");
    QCOMPARE(converted,
             QString(R"(<p><a href="http://wikipedia.org/wiki/Dawn of War">Dawn of War</a></p>)" "\n"
                     R"(<p><a href="http://wikipedia.org/wiki/Dawn of War" title="Dawn of War">Dawn of War</a></p>)"));
}
