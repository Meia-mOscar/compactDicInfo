#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//Elements
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QProgressBar>
//Layout
#include <QTableView>
#include <QStandardItemModel>
#include <QStringList>
#include <QHeaderView> //Sorting rows
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <RatingDelegate.h>

#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    //Have the table .show()
    ~MainWindow();

public slots:
    void addClicked();
    void deleteClicked();
    void selectedRow(const QModelIndex &index);
    void orderClicked(int logicalIndex);

private:
    void clearInputs();
    //Input fields
    QLabel *composerLabel = new QLabel("Composer");
    QLineEdit *composerInput = new QLineEdit;
    QLabel *albumTitleLabel = new QLabel("Album title");
    QLineEdit *albumTitleInput = new QLineEdit;
    QLabel *replacementCostLabel = new QLabel("Replacement cost (R)");
    QDoubleSpinBox *replacementCostInput = new QDoubleSpinBox;
    QLabel *ratingLabel = new QLabel("Rating");
    QSpinBox *ratingInput = new QSpinBox;
    QLabel *placeholderLabel = new QLabel;
    //Pushbuttons
    QPushButton *addRow = new QPushButton("Add");
    QPushButton *deleteRow = new QPushButton("Delete");
    //Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *inputsLayout = new QHBoxLayout;
        QVBoxLayout *composerLayout = new QVBoxLayout;
        QVBoxLayout *albumTitleLayout = new QVBoxLayout;
        QVBoxLayout *replacementCostLayout = new QVBoxLayout;
        QVBoxLayout *ratingLayout = new QVBoxLayout;
        QVBoxLayout *addACtionLayout = new QVBoxLayout;
    QTableView *tableView = new QTableView; //Table view
    QWidget *centralWidget = new QWidget;
    //Container
    QStandardItemModel *table = new QStandardItemModel;
    int rowCount;
    RatingDelegate *progressbarDelegate = new RatingDelegate;
    int selectedRowIndex;
};

#endif // MAINWINDOW_H
