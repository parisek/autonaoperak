# How to run
1. Install [ddev](https://ddev.readthedocs.io/en/stable/#installation)
2. Start docker with command `ddev start` in project root directory
3. Import database with command `ddev import-db --file=db.sql` (replace with actual db name)
4. Run `ddev describe` to view docker settings
5. Use `ddev stop`
6. Use `ddev drush status` to access Drush
7. Use `ddev ssh` and now you can use all commands
8. User `ddev auth ssh` or `ddev auth ssh -d ~/.ssh/ddev` to add keys
