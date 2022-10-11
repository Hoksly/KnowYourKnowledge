## General Moments

### Everything is a Knowledge Item. 
#### KnowledgeItem 
KnowledgeItem - abstract class, that is parental for all other items
**Unique fields: _title, creation_time,  id: **


### Information Classes 
These classes, such as TextNote, Comment, etc. are inherited from KnowledgeItem. Their main function – to store a specific type of information. 

Documentation and description for each specific class could be found (in future) in InformationClasses directory 


### Storage Classes
#### Storage : Inherited from KnowledgeItem
Storage—abstract class to store other items. Inherited from KnowledgeItem. 

**Additional fields: container :  can store objects of different types, but all of them are inherited from KnowledgeItem. 

#### Other Storage classes
Other storage classes, such as Directory and TextNoteCollection are inherited from Storage.

Documentation and description for each specific class could be found (in future) in StorageClasses directory


### Other Classes 
This classes implement specific functions, such as loading/exporting items etc. and are not inherited from KnowledgeItem


### Comments
1) id in KnowledgeItem - should have   **id_T**  that is synonym to **base32**  type