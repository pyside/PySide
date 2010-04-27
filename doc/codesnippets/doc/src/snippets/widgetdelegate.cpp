
//![0]
class WidgetDelegate (QStyledItemDelegate):
    # ...

    def paint(painter, option, index):
        if index.column() == 1:
            progress = index.data().toInt()

            progressBarOption = QStyleOptionProgressBar()
            progressBarOption.rect = option.rect
            progressBarOption.minimum = 0
            progressBarOption.maximum = 100
            progressBarOption.progress = progress
            progressBarOption.text = QString::number(progress) + "%"
            progressBarOption.textVisible = True

            QApplication.style().drawControl(QStyle.CE_ProgressBar, progressBarOption, painter)
        else:
            QStyledItemDelegate.paint(self, painter, option, index)

//![0]

