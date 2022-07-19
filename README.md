# OwnersTableTest

Prefix for zero-made classes - "TOT".

Every change in existed classes marked with #pragma region ForTest or // ForTest 

-----

Every Actor that should works with DataTable should have 3 additional components:

TOTOwnerComponent - Store OwnerInfo for this actor.

TOTOwnerInfoWidgetcomponent - To send info to TOTOwnerInfoWidget.

BoxCollisionComponent - To show widget on overlap.

-----

To change OwnerInfo for actor you can press E when aiming at actor.

Sorting by Sex is enabled in c++ only. Have no time to make widget functional.

You can search by IDs, Names or Sex. Just press on button near search field.

To change owner you can select Row in widget and press Change Owner button.

Icons were made from one texture by creating material, cutting and "animating" them in material instances.

You can change start OwnerInfo only for instances of actors.

All zero-made blueprints exists in ForTest folder.