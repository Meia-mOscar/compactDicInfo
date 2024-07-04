#include <RatingDelegate.h>

void RatingDelegate::setIndex(int column){
    progressBarColumn = column;
}

void RatingDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid() && index.column() == progressBarColumn){
        int rating = index.data(Qt::DisplayRole).toInt();
        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = rating;
        progressBarOption.textVisible = false;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
