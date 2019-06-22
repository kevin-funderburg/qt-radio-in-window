#include <QtGui>

#include "radio.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    // Create textedit area for main window
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
    // Initialize the acitions for the menus
    createActions();
    // Add the actions to the menus
    createMenus();
    createStatusBar();
    // Create dock widget area populated with Radio class
    // created previously
    createDockWindows();

    setWindowTitle(tr("Dock Widgets"));
    newTxt();
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createActions()
{
    /// Each action below is created with shortcuts, a status tip,
    /// and then is connected to slot function that will perform
    /// the desired action.
    newAct = new QAction(tr("&New File"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new form letter"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newTxt()));

    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current form letter"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a text file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    undoAct = new QAction(tr("&Undo..."), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last change"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    // Instantiate the menu bars with their respective actions
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::newTxt()
{
    //set the text area to default
    textEdit->clear();

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);
    QTextFrame *topFrame = cursor.currentFrame();
    QTextFrameFormat topFrameFormat = topFrame->frameFormat();
    topFrameFormat.setPadding(16);
    topFrame->setFrameFormat(topFrameFormat);
    QTextCharFormat textFormat;

    QString defTxt= "This is the default text for a new file.";
    cursor.insertText(defTxt, textFormat);
}

// Save the current text in the text area to a file
void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Choose a file name"), ".",
                                                    tr("Text files (*.txt)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                                     .arg(fileName)
                                     .arg(file.errorString()));
        return;
    }

    // load the file into the QTextStream
    QTextStream out(&file);
    // Set the str to the textEdit's contents
    QString str = textEdit->toPlainText();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Write str to the output file
    out << str;
    QApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                                    tr("Text files (*.txt)"));
    // Ensure file is exists and is editable
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot open file %1:\n%2.")
                                     .arg(fileName)
                                     .arg(file.errorString()));
        return;
    }

    QString str;
    QTextStream in(&file);
    str = in.readAll();

    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Set contents of textEdit to contents of chosen file
    textEdit->setPlainText(str);
    QApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Opening '%1'").arg(fileName), 2000);
}

void MainWindow::undo()
{
    QTextDocument *document = textEdit->document();
    document->undo();
}

// Simple about window located within the help menu
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Dock Widgets With Radio"),
                       tr("The <b>Dock Widgets</b> example demonstrates how to "
                          "use Qt's dock widgets. You can open files within the "
                          "text editor pane, enter your own text, and save files "
                          "to the system."));
}

void MainWindow::createStatusBar() { statusBar()->showMessage(tr("Ready")); }

/// Creates dock widget object that loads the Radio widget
/// created previously
void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("radio"), this);
    QWidget *radio = new Radio;
    dock->setWidget(radio);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    // Add toggle button in the view menu
    viewMenu->addAction(dock->toggleViewAction());
}
