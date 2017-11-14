#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <git/oid.h>
#include <git/repository.h>

int main(int argc, char* argv[]) {
    auto r = yaga::git::repository::open("/");
    auto e = r.error();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///");
    engine.addImportPath("qrc:///Components");
    engine.addImportPath("qrc:///Pages");
    engine.load(QUrl(QLatin1String("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
