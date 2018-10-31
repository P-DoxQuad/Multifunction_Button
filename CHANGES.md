#CHANGES

V2.4:
- Formatted and added comments.
- Used C-style wait function (replaced 'DELAY'), not Arduino reliant.
- Debounce And Edge Detection Are All Included Inside Button Function. 
- Seperated Button function from main code. Implemented in 'button.c' and 'button.h'

V2.3:
- Removed all Debounce for switch filtering.

V2.2:
- Cleaned up code.
- Included third timed gesture.

V2:
- Debounce Switch Filtering.
- Rename variables and improved timed logic.
- Moved Button function implementation back inside the main source.

V1.1:
- Seperated Button function from main code. Implemented in 'button.c' and 'button.h'
