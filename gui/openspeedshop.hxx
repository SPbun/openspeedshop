////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////
  


#ifndef OPENSPEEDSHOP_H
#define OPENSPEEDSHOP_H

#include <qvariant.h>
#include <qmainwindow.h>
#include "PanelContainer.hxx"
#include <qassistantclient.h>

#include "preferencesdialog.hxx"

#include <qfile.h>   // For the file dialog box.
#include <qfiledialog.h>  // For the file dialog box.

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;

class CLIInterface;

typedef QValueList<QWidget *> PreferencesStackPagesList;

//! The main window skeleton containing statusBar and menubar.
class OpenSpeedshop : public QMainWindow
{
    //! Q_OBJECT is needed as there are slots defined for the OpenSpeedshop
    Q_OBJECT

  public:
    //! Constructor for the QMainWindow.
    OpenSpeedshop( int wid=0, QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );

    //! Destructor for the QMainWindow.
    ~OpenSpeedshop();

    //! The mainwindow menu bar.
    QMenuBar *menubar;
    QPopupMenu *fileMenu;
    QPopupMenu *editMenu;
    QPopupMenu *helpMenu;

    QAction* fileLoadNewAction;
    QAction* fileAttachNewProcessAction;

    QAction* fileOpenExperimentAction;
    QAction* fileOpenSavedExperimentAction;
    QAction* fileSaveExperimentAction;
    QAction* fileExportExperimentDataAction;
    QAction* fileSaveSessionAction;
    QAction* filePreferencesAction;
    QAction* fileCloseAction;
    QAction* fileExitAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;

    QAssistantClient *assistant;

    CLIInterface *cli;

    //! A list to all plugin panel preferences 
    PreferencesStackPagesList preferencesStackPagesList;

    //! A pointer to the top PanelContainer that is parented to this mainwindow.
    PanelContainer *topPC;

    //! The window id string associated with the cli
    QString widStr;

    //! The hinted process id string that is to be attached (eventually).
    QString pidStr;

    //! The host to the peruse.
    QString hostStr;

    //! The hinted executable_name that is to be loaded (eventually).
    QString executableName;

    //! The args to the executable that is to be loaded (eventually).
    QString argsStr;

    //! The experiment to attach to
    QString expStr;

    //! The thread/rank to attach to
    QString rankStr;

    //! The hinted experiment_name that is to be intialized.. 
    QString experimentName;

    //! The load file dialog.
    QFileDialog *lfd;

    //! The save file dialog.
    QFileDialog *sfd;

    PreferencesDialog *preferencesDialog;
    //! print out some internal debug information about this class.
    void print();


    void fileLoadNewProgram();
    void fileAttachNewProcess();
  public slots:
    virtual void fileOpenExperiment();
    virtual void fileOpenSavedExperiment();
    virtual void fileSaveExperiment();
    virtual void fileExportExperimentData();
    virtual void fileSaveSession();
    virtual void filePreferences();
    virtual void fileClose();
    virtual void fileExit();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();

    virtual void loadNewProgram();
    virtual void attachNewProcess();
protected:
    //! A vertical box to place the child widgets.
    QVBoxLayout* OpenSpeedshopLayout;

protected slots:
    //! Change the language by calling tr().
    virtual void languageChange();

private:
    //! Routine that is call after initial setup.
    void init();

    //! Routine that is call just pior to this class' destructor.
    void destroy();
};

#endif // OPENSPEEDSHOP_H
