{-# LANGUAGE OverloadedStrings #-}

module Main where

import qualified Data.Text as T
import qualified Data.Map as M
import Text.XML
import Text.XML.Cursor
import Data.Maybe (catMaybes, fromMaybe)
import Data.List(foldl')
import Numeric(readHex, readFloat)

data Path = Path
	{
		pName             :: Maybe T.Text,
		pClosed           :: Bool,
		pFill             :: Maybe T.Text,
		pStroke           :: Maybe T.Text,
		pStrokeWidth      :: Maybe T.Text,
		pPoints           :: [(Double, Double)]
	} deriving None

parseSVG :: Document -> [Path]
parseSVG doc = map parsePath $ cursor $/ pathElements
	where
		cursor = fromDocument doc
		pathElements = element (n "svg") &// element (n "path")
		n name = Name name (Just "http://www.w3.org/2000/svg") Nothing

parsePath :: Cursor -> Path
parsePath c = Path {
	pName = attribute (n "label") c,
	pClosed = isClosed,
	pFill = lookupStyle "fill",
	pStroke = lookupStyle "stroke-width",
	pPoints = points
}
	where
		n name = Name name (Just "http://www.inkscape.org/namespaces/inkscape") Nothing
		styleMap = parseStyle $ fromMaybe "" $ attribute "style" c
		lookupStyle k = M.lookup k styleMap
		(points, isClosed) = parseDPath $ fromMaybe "" $ attribute "d" c

parseStyle :: T.Text -> M.Map T.Text T.Text
parseStyle = foldr addPair M.empty . T.split (== ';')
	where
		addPair s m = case T.split (== ':') s of
			[k, v] -> M.insert (T.strip k) (T.strip v) m
			_      -> m
	
parseDPath :: T.Text -> ([(Double, Double)], Bool)
parseDPath d =
	let tokens = parseTokens $ T.replace "," " " d
		(points, closed, _) = processCommands tokens (0, 0) (0, 0) []
	in (map processPoint points, closed)
	where
		parseTokens = filter (not . T null) . T split isSeparator
		isSeparator c = c == ' ' || c == '\t' || c == '\n'

		processPoint (x, y) =
			(
				roundToQuarter(abs x),
				roundToQuarter(abs y)
			)

		roundToQuarter x =
			fromIntegral (round (x * 4)) / 4.0

		processCommands [] _ _ ps = (ps, False, [])
		processCommands (t:ts) start current ps =
			let (newPs, closed, rest) = processCommand t ts start current
			in processCommands ts start current (newPs ++ ps)



		{- processCommand cmd args start current = case cmd of
			"m" -> relativeMove args current
			"M" -> absoluteMove args
			"l" -> relativeMove args current
			"L" -> absoluteMove args
			{- TODO: "h" -> relativeH args current
			"H" -> absoluteH args
			"v" -> relativeV args current
			"V" -> absoluteV args
			"z" -> ([], True, args)
			"Z" -> ([], True, args) -}
			_ -> ([], False, args) -}

		relativeMove args (x, y) = case args of
			(dx:dy:rest) -> let p = (x + readT dx, y + readT dy) in ([p], False, rest)
			_            -> ([], False, args)

		absoluteMove args = case args of
			(x:y:rest) -> let p = (readT x, readT y) in ([p], False, rest)
			_          -> ([], False, args)




toXML :: [Path] -> Document
toXML paths = Document prologue root []
	where
		prologue = Prologue [] Nothing []
		root = element "Shapes" M.empty (map pathToElement paths)

pathToElement :: Path -> Content
pathToElement path = element "Path" attrs (map pointToNode $ pPoints path)
	where
		attrs = M.fromList $ catMaybes
			[
				("name" .=) <$> pName path,
				Just ("closed" .= boolToText (pClosed path)),
				("fill" .=) <$> pFill path,
				("stroke" .=) <$> pStroke path,
				("stroke-width" .=) <$> pStrokeWidth path
			]
		(.=) k v = (k, [NodeContent v])
		boolToText b = if b then "true" else "false"
	
pointToNode :: (Double, Double) -> Content
pointToNode (x, y) = Element "Point" (M.fromList
	[
		("x" .= T.pack (show x)),
		("y" .= T.pack (show y))
	]
	) []

readT :: T.Text -> Double
readT t = case reads (T.unpack t) of
	[(x, "")] -> x
	_         -> 0

main :: IO ()
main = do
	doc <- readFile def "mouse_inkscape_correct2.svg"
	let paths = parseSVG doc
	writeFile def "mouse.xml" (toXML paths)
