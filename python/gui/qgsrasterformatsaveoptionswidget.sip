
class QgsRasterFormatSaveOptionsWidget : QWidget
{
%TypeHeaderCode
#include <qgsrasterformatsaveoptionswidget.h>
%End

  public:

    enum Type
    {
      Default, // everything except profile buttons (save as dlg)
      Full, // everything (options dlg)
      Table, // just table
      LineEdit, // just the line edit
      ProfileLineEdit // Profile + LineEdit
    };

    QgsRasterFormatSaveOptionsWidget( QWidget* parent /TransferThis/ = 0, const QString& format = "GTiff",
                                      QgsRasterFormatSaveOptionsWidget::Type type = Default,
                                      const QString& provider = "gdal" );
    ~QgsRasterFormatSaveOptionsWidget();

    void setFormat( const QString& format );
    void setProvider( const QString& provider );
    void setRasterLayer( QgsRasterLayer* rasterLayer );
    void setRasterFileName( const QString& file );
    QStringList options() const;
    void setType( QgsRasterFormatSaveOptionsWidget::Type type = Default );
    void setPyramidsFormat( QgsRaster::RasterPyramidsFormat format );

  public slots:

    void apply();
    void helpOptions();
    QString validateOptions( bool gui = true, bool reportOk = true );
    void updateProfiles();

  private slots:

    void on_mProfileNewButton_clicked();
    void on_mProfileDeleteButton_clicked();
    void on_mProfileResetButton_clicked();
    void on_mOptionsAddButton_clicked();
    void on_mOptionsDeleteButton_clicked();
    void on_mOptionsLineEdit_editingFinished();
    void optionsTableChanged();
    void optionsTableEnableDeleteButton();
    void updateOptions();
    void swapOptionsUI( int newIndex = -1 );
    void updateControls();

  protected:
    virtual void showEvent( QShowEvent * event );

  signals:
    void optionsChanged();

  private:

    QString settingsKey( QString profile ) const;
    QString currentProfileKey() const;
    QString createOptions( const QString& profile ) const;
    void deleteCreateOptions( const QString& profile );
    void setCreateOptions();
    void setCreateOptions( const QString& profile, const QString& options );
    void setCreateOptions( const QString& profile, const QStringList& list );
    QStringList profiles() const;
    bool eventFilter( QObject *obj, QEvent *event );

};
