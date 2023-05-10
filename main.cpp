#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <QAbstractListModel>

#include "mainmodels.h"

int main(int argc, char *argv[]) {
    /*
    //dp
    std::cout << kp::makeTask< kp::Object1_0 <kp::Bug1>, kp::Bug1>({ {5, 1}, {6, 7}, {9, 10}, {12, 13} }, { 18 }) << std::endl;
    std::cout << kp::makeTask< kp::ObjectUnlimited<kp::Bug1>, kp::Bug1>({ {5, 1}, {6, 7}, {9, 10}, {12, 13} }, { 18 }) << std::endl;
    std::cout << kp::makeTask< kp::ObjectLimited <kp::Bug1>, kp::Bug1>({ {5, 1, 3}, {6, 7, 3}, {9, 10, 3}, {12, 13, 3} }, { 4 }) << std::endl;

    //experimantal recursive
    std::cout << kp::makeTask< kp::Object1_0 <kp::Bug2>, kp::Bug2>({ {5, 1, 3}, {6, 7, 7}, {9, 10, 8}, {12, 13,9} }, { 18, 12 }) << std::endl;
    std::cout << kp::makeTask< kp::ObjectUnlimited <kp::Bug2>, kp::Bug2>({ {5, 4, 3}, {6, 7, 7}, {9, 10, 8}, {12, 13,9} }, { 18, 12 }) << std::endl;
    std::cout << kp::makeTask< kp::ObjectLimited <kp::Bug2>, kp::Bug2>({ {5, 4, 1, 3}, {6, 3, 7, 7}, {9, 4, 10, 8}, {12, 3, 13, 9} }, { 18, 12 }) << std::endl;

    //пример из документа
    std::cout << kp::makeTask< kp::ObjectUnlimited <kp::Bug2>, kp::Bug2>({ {70, 12, 60}, {40, 6, 40} }, { 74, 420 }) << std::endl;
    */
    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MathProject_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    qmlRegisterSingletonType<MainModel1_0_1>("my_types.test.t",1,0, "MainModel1_0_1", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModel1_0_1* model = new MainModel1_0_1; //owner ship is qml
                return model;
    });
    qmlRegisterSingletonType<MainModelUnlimited_1>("my_types.test.t",1,0, "MainModelUnlimited_1", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModelUnlimited_1* model = new MainModelUnlimited_1; //owner ship is qml
                return model;
    });
    qmlRegisterSingletonType<MainModelLimited_1>("my_types.test.t",1,0, "MainModelLimited_1", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModelLimited_1* model = new MainModelLimited_1; //owner ship is qml
                return model;
    });
    qmlRegisterSingletonType<MainModel1_0_2>("my_types.test.t",1,0, "MainModel1_0_2", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModel1_0_2* model = new MainModel1_0_2; //owner ship is qml
                return model;
    });
    qmlRegisterSingletonType<MainModelUnlimited_2>("my_types.test.t",1,0, "MainModelUnlimited_2", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModelUnlimited_2* model = new MainModelUnlimited_2; //owner ship is qml
                return model;
    });
    qmlRegisterSingletonType<MainModelLimited_2>("my_types.test.t",1,0, "MainModelLimited_2", [](QQmlEngine *engine, QJSEngine *scriptEngine)->QObject* {
                Q_UNUSED(engine)
                Q_UNUSED(scriptEngine)
                static MainModelLimited_2* model = new MainModelLimited_2; //owner ship is qml
                return model;
    });
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/MathProject/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();

}
