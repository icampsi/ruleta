/*
 * Ruleta - by Ignasi Camps
 *
 * Copyright (c) 2024 Ignasi Camps
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QMenubar>
#include <QFontDatabase>

#include "ui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/Chewy-Regular.ttf");
    if (id == -1) {
        qDebug() << "Could not load Chewy font";
    } else {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        qApp->setProperty("chewyFontFamily", family);
    }

    MainWindow MainWindow;
    MainWindow.showFullScreen();

    MainWindow.show();
    MainWindow.menuBar()->hide();

    return app.exec();
}
