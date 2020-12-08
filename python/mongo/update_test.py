def have_permission_by_name(_plat, _app, perm, user=None):
    """type (string, string, enums.AppPermission, string) -> Boolean"""
    app = get_by_name(_plat, _app)
    return have_permission_by_app(app, perm, user)


def have_permission_by_id(app_id, perm, user=None):
    """type (string, string, enums.AppPermission, string) -> Boolean"""
    app = get_by_id(app_id)
    return have_permission_by_app(app, perm, user)


def have_permission_by_criteria(criteria, perm, user=None):
    """type (string, string, enums.AppPermission, string) -> Boolean"""
    app = get_by_criteria(criteria)
    return have_permission_by_app(app, perm, user)
