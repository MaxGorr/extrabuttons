#include "Parser.h"

#include "Path.h"
#include "VariablesManager.h"

#include <QtXmlPatterns>

#include <QDebug>
#include <QDomDocument>
#include <QDomNodeList>
#include <QFile>

//#define NAMED(_var_) #_var_ ":" << _var_ << ";"

namespace {
    const QString BASIC_CONTENT =
        "<config>\n"
        "  <vars>\n"
        "    <!-- <var name=\"VAR_FROM_VARS\" val=\"someValue\" /> -->\n"
        "  </vars>\n"
        "  <cmds>\n"
        "    <!-- <cmd name=\"justName\" val=\"path/to/file\" /> -->\n"
        "    <!-- You can use varibales: -->\n"
        "    <!-- <cmd name=\"useSysVar\" val=\"${SYS_VAR}/file\" /> -->\n"
        "    <!-- <cmd name=\"useVarFromVars\" val=\"${VAR_FROM_VARS}/file\" /> -->\n"
        "    <!-- Command with shortcut \"Alt+S\": -->\n"
        "    <!-- <cmd name=\"nameWith&amp;Shortcut\" val=\"cmd4\" /> -->\n"
        "  </cmds>\n"
        "</config>\n";
}

Parser::Parser(QObject *parent) : QObject(parent) { }

void Parser::fromFile()
{
    QFile setsFile(Path::instance().buttonsSettings());
    if (!setsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open settings file!";
        if (setsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&setsFile);
            stream << BASIC_CONTENT;
            setsFile.close();
        }
        emit dataParsingFinished();
        return;
    }
    VariablesManager::clear();

    QString setsContent = setsFile.readAll();
    setsFile.close();

    // common variables
    QXmlQuery query;
    query.setFocus(setsContent);
    QString result;
    QDomDocument domdoc;
    QDomNodeList nodeList;
    int listSize = 0;

    // parse variables
    query.setQuery("/config/vars");
    if (!query.isValid()) {
        qDebug() << "Invalid query for variables!";
        emit dataParsingFinished();
        return;
    }

    query.evaluateTo(&result);
    domdoc.setContent(result);
    nodeList = domdoc.elementsByTagName("var");
    listSize = nodeList.size();
    for (int i = 0; i < listSize; i++) {
        QDomNode node = nodeList.at(i);
        QDomNamedNodeMap map = node.attributes();
        if (map.size() != 2) {
            qDebug() << "Wrong attributes count for variables!";
            emit dataParsingFinished();
            return;
        }
        if (!map.contains("name") || !map.contains("val")) {
            qDebug() << "Wrong attributes in var tag";
            emit dataParsingFinished();
            return;
        }
        QDomAttr name = map.namedItem("name").toAttr();
        QDomAttr val = map.namedItem("val").toAttr();
        VariablesManager::addVariable(name.value(), val.value());
    }

    // parse commands
    query.setQuery("/config/cmds");
    if (!query.isValid()) {
        qDebug() << "Invalid query for commands!";
        emit dataParsingFinished();
        return;
    }

    query.evaluateTo(&result);
    domdoc.setContent(result);
    nodeList = domdoc.elementsByTagName("cmd");
    listSize = nodeList.size();
    for (int i = 0; i < listSize; i++) {
        QDomNode node = nodeList.at(i);
        QDomNamedNodeMap map = node.attributes();
        if (map.size() != 2) {
            qDebug() << "Wrong attributes count!";
            emit dataParsingFinished();
            return;
        }
        if (!map.contains("name") || !map.contains("val")) {
            qDebug() << "Wrong attributes in cmd tag";
            emit dataParsingFinished();
            return;
        }
        auto name = map.namedItem("name").toAttr().value();
        auto val = map.namedItem("val").toAttr().value();
        emit dataParsed(name, VariablesManager::replace(val));
    }
    emit dataParsingFinished();
}
