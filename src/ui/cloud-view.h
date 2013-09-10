#ifndef SEAFILE_CLIENT_CLOUD_VIEW_H
#define SEAFILE_CLIENT_CLOUD_VIEW_H

#include <QWidget>
#include "account.h"

class QPoint;
class QMenu;
class QTimer;
class QShowEvent;
class QHideEvent;
class QWidgetAction;
class QToolButton;

class ListReposRequest;
class ServerRepo;
class RepoTreeView;
class RepoTreeModel;

class CloudView : public QWidget
{
    Q_OBJECT
public:
    CloudView(QWidget *parent=0);
    QWidgetAction *getAccountWidgetAction() { return account_widget_action_; }

    const Account& currentAccount() { return current_account_; }

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public slots:
    void showAddAccountDialog();
    void deleteAccount();

private slots:
    void refreshRepos();
    void refreshRepos(const std::vector<ServerRepo>& repos);
    void refreshReposFailed();
    void setCurrentAccount(const Account&account);
    void updateAccountMenu();
    void onAccountItemClicked();

private:
    Q_DISABLE_COPY(CloudView)

    void prepareAccountButtonMenu();
    void createLoadingView();
    QAction *makeAccountAction(const Account& account);
    void showLoadingView();
    void showRepos();
    bool hasAccount();

    bool in_refresh_;
    QTimer *refresh_timer_;

    RepoTreeModel *repos_model_;

    RepoTreeView *repos_tree_;
    QWidget *loading_view_;

    ListReposRequest *list_repo_req_;

    // FolderDropArea *drop_area_;
    Account current_account_;

    // Account operations
    QAction *add_account_action_;
    QAction *delete_account_action_;
    QAction *switch_account_action_;
    QMenu *account_menu_;
    QWidgetAction *account_widget_action_;
    QToolButton *account_tool_button_;
};


#endif  // SEAFILE_CLIENT_CLOUD_VIEW_H
