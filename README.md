# Cargo Chaos Setup Instructions

## If using XCode
1. Clone the repository
  - Using the terminal, navigate to your Xcode project directory
  - Navigate one level deeper than the `.xcodeproj` file into the folder with main.cpp
  - Use `git clone URL .` (the dot is important!) to clone the directory

2. Set Custom Working Directory
  - Navigate to `Product -> Scheme -> Edit Scheme` in Xcode
  - Check the box labeled `Use Custom Working Directory` and choose the same directory you cloned the repository into.
