/*
 * cl
 * Copyright (C) 2025 Game1024
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "themeutils.h"
#include <QStyleFactory>
#include <QPalette>
#include <QColor>
#include <QSettings>
#include <QApplication>
#include <QStyle>

void ThemeUtils::applyTheme(Theme theme)
{
    if (theme == System) {
        if (isSystemDarkMode()) {
            setDarkTheme();
        } else {
            setLightTheme();
        }
    } else if (theme == Dark) {
        setDarkTheme();
    } else {
        setLightTheme();
    }
}

void ThemeUtils::setDarkTheme()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    if (!app) return;

    // 深色模式必须使用 Fusion 风格，因为 WindowsVista 风格强制使用浅色控件
    app->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    QColor darkColor = QColor(45, 45, 45);
    QColor disabledColor = QColor(127, 127, 127);

    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(18, 18, 18));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

    app->setPalette(darkPalette);
    app->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

void ThemeUtils::setLightTheme()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    if (!app) return;

    // 浅色模式优先使用 WindowsVista (原生) 风格
    QStyle* style = QStyleFactory::create("Fusion");
    if (!style) {
        style = QStyleFactory::create("Windows");
    }
    app->setStyle(style);
    
    // 恢复默认调色板
    app->setPalette(style->standardPalette());
    
    // 清除全局样式表
    app->setStyleSheet("");
}

bool ThemeUtils::isSystemDarkMode()
{
#ifdef Q_OS_WIN
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme", 1).toInt() == 0;
#else
    return false; 
#endif
}
