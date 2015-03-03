/* display_filter_edit.h
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef DISPLAYFILTEREDIT_H
#define DISPLAYFILTEREDIT_H

#include "syntax_line_edit.h"

class QCompleter;
class QEvent;
class QStringListModel;
class QToolButton;

class DisplayFilterEdit : public SyntaxLineEdit
{
    Q_OBJECT
public:
    explicit DisplayFilterEdit(QWidget *parent = 0, bool plain = true);

    void setCompleter(QCompleter *c);
    QCompleter *completer() const { return completer_; }

protected:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    void paintEvent(QPaintEvent *evt);
#endif
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *evt);

public slots:
    void applyDisplayFilter();
    void displayFilterSuccess(bool success);

private slots:
    void checkFilter(const QString &text);
    void bookmarkClicked();
    void clearFilter();
    void changeEvent(QEvent* event);
    void insertFieldCompletion(const QString & completion_text);

private:
    bool plain_;
    QString placeholder_text_;
    QToolButton *bookmark_button_;
    QToolButton *clear_button_;
    QToolButton *apply_button_;
    QCompleter *completer_;
    QStringListModel *completion_model_;

    void buildCompletionList(const QString& field_word);
    // x = Start position, y = length
    QPoint getFieldUnderCursor();

signals:
    void pushFilterSyntaxStatus(const QString&);
    void popFilterSyntaxStatus();
    void pushFilterSyntaxWarning(const QString&);
    void filterPackets(QString& new_filter, bool force);
    void addBookmark(QString filter);
};

#endif // DISPLAYFILTEREDIT_H

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
