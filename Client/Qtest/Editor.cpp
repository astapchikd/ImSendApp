#include "Editor.h"

Editor::Editor(bool isConsole, QWidget* parent) : CodeEditor(isConsole, parent){
	highlighter = new Highlighter(this->document());
}

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent){
    QRegularExpression expr("\\b(warning)\\b", QRegularExpression::CaseInsensitiveOption);
    QTextCharFormat format;            
    format.setForeground(              
        QColor(Qt::yellow).lighter(130)
    );
    addHighlightningRule(expr, format);
    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor(Qt::green));
    QRegularExpression commentExpr1("\\b(OK)\\b", QRegularExpression::CaseInsensitiveOption);
    addHighlightningRule(commentExpr1, commentFormat);
    QRegularExpression expr3("\\b(error)\\b", QRegularExpression::CaseInsensitiveOption);
    QTextCharFormat format3;            
    format3.setForeground(              
        QColor(Qt::red).lighter(130)
    );
    addHighlightningRule(expr3, format3);
}
void Highlighter::addHighlightningRule(QRegularExpression pattern, QTextCharFormat format){
    rules.push_back(pattern);
    formats.push_back(format);
}
void Highlighter::highlightBlock(const QString &text){
    for (int i = 0; i < rules.size(); i++)
    {
        QRegularExpression expr = rules.at(i);
        QTextCharFormat format = formats.at(i);
        {
            QRegularExpressionMatch match = expr.match(text); //Ищем вхождение
            while (match.hasMatch()) {                        //Пока вхождение есть
                setFormat(match.capturedStart(),              //Устанавливаем формат для
                    match.capturedLength(), format);          //найденного вхождения 
                match = expr.match(text, match.capturedEnd());//Ищем следующее вхождение
            }
        }
       
    }

}