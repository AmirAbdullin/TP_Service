#ifndef CARS_H
#define CARS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QTableView>
#include <Qt>

namespace Ui {
class cars;
}

/*!
 * \class cars
 * \brief Класс cars предоставляет диалоговое окно для управления информацией об автомобилях.
 *
 * Этот класс предназначен для отображения и управления данными о машинах и их техническом обслуживании.
 * Он включает в себя функционал для добавления, просмотра и редактирования информации о ТО.
 */
class cars : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса cars.
     * \param parent Указатель на родительский виджет.
     *
     * Конструктор инициализирует новый экземпляр диалога с заданным родительским виджетом.
     * Он устанавливает начальные параметры интерфейса и инициирует подключение к базе данных.
     */
    explicit cars(QWidget *parent = nullptr);

    /*!
     * \brief Деструктор класса cars.
     *
     * Освобождает все ресурсы, связанные с объектом, и удаляет динамически созданные элементы управления.
     */
    ~cars();

private slots:
    /*!
     * \brief Обрабатывает нажатие на кнопку "Выход".
     *
     * Закрывает диалоговое окно без сохранения изменений.
     */
    void on_pushButton_3_clicked();

    /*!
     * \brief Обрабатывает нажатие на кнопку для создания нового ТО.
     *
     * Открывает новое диалоговое окно, позволяющее пользователю ввести данные для нового технического обслуживания.
     */
    void on_pushButton_clicked();

    /*!
     * \brief Обрабатывает нажатие на кнопку для просмотра списка ТО.
     *
     * Отображает список всех технических обслуживаний для выбранного автомобиля в новом окне или панели.
     */
    void on_repairsListButton_clicked();

    /*!
     * \brief Реагирует на выбор строки в таблице автомобилей.
     * \param index Индекс выбранной строки в таблице.
     *
     * Разблокирует кнопки управления, позволяя пользователю выполнить действия с выбранным автомобилем.
     */
    void on_carsTable_clicked(const QModelIndex &index);

private:
    Ui::cars *ui; ///< Указатель на форму пользовательского интерфейса, созданную с помощью Qt Designer.
    QSqlDatabase db; ///< Экземпляр базы данных для выполнения запросов.
    QSqlQuery *query; ///< Указатель на объект запроса для взаимодействия с базой данных.
    QSqlTableModel *model; ///< Модель данных для таблицы автомобилей.
    QSqlTableModel *model2; ///< Модель данных для таблицы технических обслуживаний.
    QSqlQueryModel *querymodel; ///< Модель запросов для динамически изменяемых запросов к базе данных.

};

#endif // CARS_H
