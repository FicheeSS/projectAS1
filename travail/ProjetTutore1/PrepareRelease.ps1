$compress = @{
  Path =  Join-Path $PSScriptRoot"\Release\ProjetTutore1.exe", Join-Path $PSScriptRoot"\Ressources"
  CompressionLevel = "Fastest"
  DestinationPath = Join-Path $PSScriptRoot"\Draft.Zip"
}
Compress-Archive @compress