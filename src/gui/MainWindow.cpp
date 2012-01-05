/*
 *  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "core/Database.h"
#include "core/DataPath.h"
#include "core/Metadata.h"
#include "gui/DatabaseWidget.h"

MainWindow::MainWindow()
    : m_ui(new Ui::MainWindow())
{
    m_ui->setupUi(this);

    setWindowIcon(DataPath::applicationIcon());

    connect(m_ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(currentTabChanged(int)));
    connect(m_ui->tabWidget, SIGNAL(entrySelectionChanged(bool)), m_ui->actionEntryEdit, SLOT(setEnabled(bool)));
    connect(m_ui->tabWidget, SIGNAL(entrySelectionChanged(bool)), m_ui->actionEntryDelete, SLOT(setEnabled(bool)));

    connect(m_ui->actionDatabaseNew, SIGNAL(triggered()), m_ui->tabWidget, SLOT(newDatabase()));
    connect(m_ui->actionDatabaseOpen, SIGNAL(triggered()), m_ui->tabWidget, SLOT(openDatabase()));
    connect(m_ui->actionDatabaseSave, SIGNAL(triggered()), m_ui->tabWidget, SLOT(saveDatabase()));
    connect(m_ui->actionDatabaseSaveAs, SIGNAL(triggered()), m_ui->tabWidget, SLOT(saveDatabaseAs()));
    connect(m_ui->actionDatabaseClose, SIGNAL(triggered()), m_ui->tabWidget, SLOT(closeDatabase()));
    connect(m_ui->actionEntryNew, SIGNAL(triggered()), m_ui->tabWidget, SLOT(createEntry()));
    connect(m_ui->actionEntryEdit, SIGNAL(triggered()), m_ui->tabWidget, SLOT(editEntry()));
    connect(m_ui->actionGroupNew, SIGNAL(triggered()), m_ui->tabWidget, SLOT(createGroup()));
    connect(m_ui->actionGroupEdit, SIGNAL(triggered()), m_ui->tabWidget, SLOT(editGroup()));
    connect(m_ui->actionQuit, SIGNAL(triggered()), SLOT(close()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::currentTabChanged(int index)
{
    bool hasTab = (index != -1);

    m_ui->actionDatabaseSave->setEnabled(hasTab);
    m_ui->actionDatabaseSaveAs->setEnabled(hasTab);
    m_ui->actionDatabaseClose->setEnabled(hasTab);
    m_ui->actionEntryNew->setEnabled(hasTab);
    m_ui->actionGroupNew->setEnabled(hasTab);
    m_ui->actionGroupEdit->setEnabled(hasTab);
}