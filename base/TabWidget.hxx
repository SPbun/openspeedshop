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


#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <qwidget.h>
#include <qtabwidget.h>

class AnimatedQPushButton;
class PanelContainer;

//! This overloads QTabWidget so the tabbar can accept mouse down events.
class TabWidget : public QTabWidget
{
    Q_OBJECT
  public:
    //! default constructor.
    TabWidget( );

    //! Constructor to overload QTabWiget
    TabWidget( PanelContainer *pc, QWidget *parent=0, const char *name=0 );

    //! The default destructor
    ~TabWidget( );

    //! Sets the tabbar
    void setTabBar( QTabBar *tb );

    //! Gets the tabbar.
    QTabBar *tabBar();

  protected slots:
    //! The standard Qt slot to change language information.
    virtual void languageChange();

  private slots:
    void deletePanelButtonSelected();

  private:
    AnimatedQPushButton *cw;

    PanelContainer *_panelContainer;

};
#endif // TABWIDGET_H
