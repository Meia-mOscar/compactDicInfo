#ifndef RATINGDELEGATE_H
#define RATINGDELEGATE_H

#include <QApplication>
#include <QStyledItemDelegate>

class RatingDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setIndex(int column);
private:
   int progressBarColumn = -1;
};

#endif // RATINGDELEGATE_H
