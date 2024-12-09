#ifndef PHOTOBLOBDELEGATE_H
#define PHOTOBLOBDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <QByteArray>

class PhotoBlobDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit PhotoBlobDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 6) { // Supposons que la colonne 6 contient les données BLOB
            QByteArray imageData = index.data().toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);

            if (!pixmap.isNull()) {
                QRect rect = option.rect;
                QPixmap scaledPixmap = pixmap.scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                painter->drawPixmap(rect.x(), rect.y(), scaledPixmap);
            } else {
                QStyledItemDelegate::paint(painter, option, index);
            }
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 6) { // Colonne pour la photo
            return QSize(100, 100); // Taille par défaut des images
        }
        return QStyledItemDelegate::sizeHint(option, index);
    }
};
#endif // PHOTOBLOBDELEGATE_H
