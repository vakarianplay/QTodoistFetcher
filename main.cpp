#include <QCoreApplication>
#include "todoistdata.h"


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // QNetworkAccessManager manager;
    // fetchTasksAssignedToMe(manager);
    TodoistData todoist;


    return app.exec();
}
