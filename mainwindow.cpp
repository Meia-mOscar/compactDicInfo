#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Music");

    //Initialise central widget outline
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    mainLayout->addLayout(inputsLayout);
        inputsLayout->addLayout(composerLayout);
            composerLayout->addWidget(composerLabel);
            composerLayout->addWidget(composerInput);
        inputsLayout->addLayout(albumTitleLayout);
            albumTitleLayout->addWidget(albumTitleLabel);
            albumTitleLayout->addWidget(albumTitleInput);
        inputsLayout->addLayout(replacementCostLayout);
            replacementCostLayout->addWidget(replacementCostLabel);
            replacementCostLayout->addWidget(replacementCostInput);
        inputsLayout->addLayout(ratingLayout);
            ratingLayout->addWidget(ratingLabel);
            ratingLayout->addWidget(ratingInput);
        inputsLayout->addLayout(addACtionLayout);
            addACtionLayout->addWidget(placeholderLabel);
                addACtionLayout->addWidget(addRow);
    mainLayout->addWidget(tableView);
        tableView->setModel(table); //Add the table to the layoput
        tableView->setItemDelegate(progressbarDelegate);
        progressbarDelegate->setIndex(3);
    mainLayout->addWidget(deleteRow);

    //Initialise the table
    QStringList labels = (QStringList() << "Composer" << "Album titles" << "Replacement cost" << "Rating");
    table->setHorizontalHeaderLabels(labels);
    tableView->horizontalHeader()->setStretchLastSection(true);

    //Initialise input fields
    composerInput->setText("");
    albumTitleInput->setText("");
    replacementCostInput->setValue(0.00);
        replacementCostInput->setMaximum(1000000.00);
        replacementCostInput->setMinimum(0);
    ratingInput->setValue(0);
        ratingInput->setMaximum(100);
        ratingInput->setMinimum(0);
    rowCount = 0;
    selectedRowIndex = -1;

    //HeaderView used to order rows
    QHeaderView *headerView = tableView->horizontalHeader();

    //Connect signals and slots
    connect(addRow, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(headerView, &QHeaderView::sectionClicked, this, &MainWindow::orderClicked);
    connect(tableView, &QTableView::clicked, this, &MainWindow::selectedRow);
    connect(deleteRow, &QPushButton::released, this, &MainWindow::deleteClicked);
}

MainWindow::~MainWindow()
{

}

void MainWindow::orderClicked(int logicalIndex)
{
    Qt::SortOrder sortOrder = tableView->horizontalHeader()->sortIndicatorOrder();
    if(sortOrder == Qt::AscendingOrder)
    {
        sortOrder = Qt::DescendingOrder;
    }
    else
    {
        sortOrder = Qt::AscendingOrder;
    }

    tableView->horizontalHeader()->setSortIndicator(logicalIndex, sortOrder);
    tableView->sortByColumn(logicalIndex, sortOrder);
}

void MainWindow::clearInputs()
{
    composerInput->setText("");
    albumTitleInput->setText("");
    replacementCostInput->setValue(0.00);
    ratingInput->setValue(0);
}

void MainWindow::addClicked()
{
    //Convert inputs into QStandardItem
    QStandardItem *composerItem = new QStandardItem;
    composerItem->setText(composerInput->text());
    table->setItem(rowCount,0,composerItem);

    QStandardItem *albumTitleItem = new QStandardItem;
    albumTitleItem->setText(albumTitleInput->text());
    table->setItem(rowCount,1,albumTitleItem);

    QStandardItem *replacementCostItem = new QStandardItem;
    QString replacementCostValue;
    replacementCostValue = QString::number(replacementCostInput->value(), 'f', 2);
    replacementCostItem->setText(replacementCostValue);
    table->setItem(rowCount,2,replacementCostItem);

    if(replacementCostInput->value() > 200)
    {
        QBrush blush(Qt::red);
        composerItem->setBackground(blush);
        albumTitleItem->setBackground(blush);
        replacementCostItem->setBackground(blush);
    }

    //Delegate used to paint progressbar in desired column
    table->setData(table->index(rowCount,3),ratingInput->value(), Qt::DisplayRole);

    /*Remember items for deletion? Add them to a QList<T>*/

    rowCount++; //Increment the number of rows

    this->clearInputs(); //Clear the UI
}

void MainWindow::selectedRow(const QModelIndex &index)
{
    selectedRowIndex = index.row();
}

void MainWindow::deleteClicked()
{
    //Can call clear() to remove all items from the model
    //QStandardItemModel->removeRow(Index)
    qDebug() << selectedRowIndex;
    table->removeRow(selectedRowIndex);
}
